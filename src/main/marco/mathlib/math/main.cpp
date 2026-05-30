#include <chrono>
#define VK_USE_PLATFORM_WIN32_KHR  // ou VK_USE_PLATFORM_XCB_KHR no Linux
#include <vulkan/vulkan.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdexcept>

// -----------------------------------------------------------------------------
// Helper functions
// -----------------------------------------------------------------------------
static void checkResult(VkResult res, const char* msg) {
    if (res != VK_SUCCESS) {
        std::cerr << "ERRO: " << msg << " -> " << res << std::endl;
        exit(1);
    }
}

static uint32_t findMemoryType(VkPhysicalDevice physDev, uint32_t typeFilter, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties memProps;
    vkGetPhysicalDeviceMemoryProperties(physDev, &memProps);
    for (uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
        if ((typeFilter & (1 << i)) && (memProps.memoryTypes[i].propertyFlags & props) == props)
            return i;
    }
    throw std::runtime_error("tipo de memória não encontrado");
}

static void createBuffer(VkDevice device, VkPhysicalDevice physDev, VkDeviceSize size,
                         VkBufferUsageFlags usage, VkMemoryPropertyFlags memProps,
                         VkBuffer& buffer, VkDeviceMemory& memory) {
    VkBufferCreateInfo bufInfo = {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};
    bufInfo.size = size;
    bufInfo.usage = usage;
    bufInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    checkResult(vkCreateBuffer(device, &bufInfo, nullptr, &buffer), "criar buffer");

    VkMemoryRequirements memReqs;
    vkGetBufferMemoryRequirements(device, buffer, &memReqs);
    uint32_t memType = findMemoryType(physDev, memReqs.memoryTypeBits, memProps);
    VkMemoryAllocateInfo allocInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
    allocInfo.allocationSize = memReqs.size;
    allocInfo.memoryTypeIndex = memType;
    checkResult(vkAllocateMemory(device, &allocInfo, nullptr, &memory), "alocar memória");
    vkBindBufferMemory(device, buffer, memory, 0);
}

static void copyToDevice(VkDevice device, VkPhysicalDevice physDev, VkQueue queue, VkCommandPool cmdPool,
                         VkBuffer dstBuffer, const void* data, size_t size) {
    // Staging buffer
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingMemory;
    createBuffer(device, physDev, size,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingMemory);
    void* mapped;
    vkMapMemory(device, stagingMemory, 0, size, 0, &mapped);
    memcpy(mapped, data, size);
    vkUnmapMemory(device, stagingMemory);

    // Command buffer para copiar
    VkCommandBufferAllocateInfo cmdAlloc = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    cmdAlloc.commandPool = cmdPool;
    cmdAlloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdAlloc.commandBufferCount = 1;
    VkCommandBuffer cmdBuf;
    vkAllocateCommandBuffers(device, &cmdAlloc, &cmdBuf);
    VkCommandBufferBeginInfo beginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cmdBuf, &beginInfo);
    VkBufferCopy copyRegion = {0, 0, size};
    vkCmdCopyBuffer(cmdBuf, stagingBuffer, dstBuffer, 1, &copyRegion);
    vkEndCommandBuffer(cmdBuf);
    VkSubmitInfo submit = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &cmdBuf;
    vkQueueSubmit(queue, 1, &submit, VK_NULL_HANDLE);
    vkQueueWaitIdle(queue);
    vkFreeCommandBuffers(device, cmdPool, 1, &cmdBuf);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingMemory, nullptr);
}

static std::vector<float> readBuffer(VkDevice device, VkPhysicalDevice physDev, VkQueue queue,
                                     VkCommandPool cmdPool, VkBuffer srcBuffer, size_t size) {
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingMemory;
    createBuffer(device, physDev, size,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingMemory);
    VkCommandBufferAllocateInfo cmdAlloc = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    cmdAlloc.commandPool = cmdPool;
    cmdAlloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdAlloc.commandBufferCount = 1;
    VkCommandBuffer cmdBuf;
    vkAllocateCommandBuffers(device, &cmdAlloc, &cmdBuf);
    VkCommandBufferBeginInfo beginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cmdBuf, &beginInfo);
    VkBufferCopy copyRegion = {0, 0, size};
    vkCmdCopyBuffer(cmdBuf, srcBuffer, stagingBuffer, 1, &copyRegion);
    vkEndCommandBuffer(cmdBuf);
    VkSubmitInfo submit = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &cmdBuf;
    vkQueueSubmit(queue, 1, &submit, VK_NULL_HANDLE);
    vkQueueWaitIdle(queue);
    void* mapped;
    vkMapMemory(device, stagingMemory, 0, size, 0, &mapped);
    std::vector<float> result(size / sizeof(float));
    memcpy(result.data(), mapped, size);
    vkUnmapMemory(device, stagingMemory);
    vkFreeCommandBuffers(device, cmdPool, 1, &cmdBuf);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingMemory, nullptr);
    return result;
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main() {
    // 1. Instância Vulkan
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.pApplicationName = "MatrixMul";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "NoEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    instInfo.pApplicationInfo = &appInfo;
    VkInstance instance;
    checkResult(vkCreateInstance(&instInfo, nullptr, &instance), "criar instância");

    // 2. Dispositivo físico
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) throw std::runtime_error("Nenhum dispositivo Vulkan");
    std::vector<VkPhysicalDevice> physDevices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, physDevices.data());
    VkPhysicalDevice physDevice = physDevices[0];

    // Encontrar fila de compute
    uint32_t queueFamilyIdx = 0;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &queueFamilyCount, queueFamilies.data());
    bool found = false;
    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            queueFamilyIdx = i;
            found = true;
            break;
        }
    }
    if (!found) throw std::runtime_error("Nenhuma fila de compute");

    // 3. Dispositivo lógico
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    queueInfo.queueFamilyIndex = queueFamilyIdx;
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo deviceInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;
    VkDevice device;
    checkResult(vkCreateDevice(physDevice, &deviceInfo, nullptr, &device), "criar dispositivo");

    // === AQUI ESTÁ A DECLARAÇÃO QUE FALTAVA ===
    VkQueue queue;
    vkGetDeviceQueue(device, queueFamilyIdx, 0, &queue);

    // 4. Command pool
    VkCommandPoolCreateInfo poolInfo = {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
    poolInfo.queueFamilyIndex = queueFamilyIdx;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    VkCommandPool cmdPool;
    checkResult(vkCreateCommandPool(device, &poolInfo, nullptr, &cmdPool), "criar command pool");

    // 5. Dados das matrizes
    uint32_t SQUARE_SIZE = 4;
    uint32_t M = SQUARE_SIZE, K = SQUARE_SIZE, N = SQUARE_SIZE;
    size_t sizeA = M * K * sizeof(float);
    size_t sizeB = K * N * sizeof(float);
    size_t sizeC = M * N * sizeof(float);

    std::vector<float> h_A(M * K);
    std::vector<float> h_B(K * N);
    for (uint32_t i = 0; i < M; ++i)
        for (uint32_t j = 0; j < K; ++j)
            h_A[i * K + j] = static_cast<float>(i + j);
    for (uint32_t i = 0; i < K; ++i)
        for (uint32_t j = 0; j < N; ++j)
            h_B[i * N + j] = static_cast<float>(i - j);

    // 6. Buffers GPU
    VkBuffer bufferA, bufferB, bufferC;
    VkDeviceMemory memA, memB, memC;
    createBuffer(device, physDevice, sizeA,
                 VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferA, memA);
    createBuffer(device, physDevice, sizeB,
                 VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferB, memB);
    createBuffer(device, physDevice, sizeC,
                 VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferC, memC);

    copyToDevice(device, physDevice, queue, cmdPool, bufferA, h_A.data(), sizeA);
    copyToDevice(device, physDevice, queue, cmdPool, bufferB, h_B.data(), sizeB);

    // 7. Carregar shader SPIR-V
    std::ifstream shaderFile("matrix_mul.spv", std::ios::binary | std::ios::ate);
    if (!shaderFile.is_open()) throw std::runtime_error("Arquivo matrix_mul.spv não encontrado");
    size_t shaderSize = shaderFile.tellg();
    std::vector<uint32_t> shaderCode(shaderSize / sizeof(uint32_t));
    shaderFile.seekg(0, std::ios::beg);
    shaderFile.read(reinterpret_cast<char*>(shaderCode.data()), shaderSize);
    shaderFile.close();

    VkShaderModuleCreateInfo moduleInfo = {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
    moduleInfo.codeSize = shaderSize;
    moduleInfo.pCode = shaderCode.data();
    VkShaderModule shaderModule;
    checkResult(vkCreateShaderModule(device, &moduleInfo, nullptr, &shaderModule), "criar shader module");

    // 8. Descriptor set layout
    VkDescriptorSetLayoutBinding bindings[3] = {};
    for (int i = 0; i < 3; ++i) {
        bindings[i].binding = i;
        bindings[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        bindings[i].descriptorCount = 1;
        bindings[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    }
    VkDescriptorSetLayoutCreateInfo layoutInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    layoutInfo.bindingCount = 3;
    layoutInfo.pBindings = bindings;
    VkDescriptorSetLayout descriptorSetLayout;
    checkResult(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout), "criar DS layout");

    // 9. Pipeline layout com push constants
    VkPushConstantRange pushRange = {};
    pushRange.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    pushRange.offset = 0;
    pushRange.size = 3 * sizeof(uint32_t);
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushRange;
    VkPipelineLayout pipelineLayout;
    checkResult(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout), "criar pipeline layout");

    // 10. Compute pipeline
    VkPipelineShaderStageCreateInfo stageInfo = {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO};
    stageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    stageInfo.module = shaderModule;
    stageInfo.pName = "main";
    VkComputePipelineCreateInfo pipelineInfo = {VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO};
    pipelineInfo.stage = stageInfo;
    pipelineInfo.layout = pipelineLayout;
    VkPipeline pipeline;
    checkResult(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline), "criar pipeline");

    // 11. Descriptor pool e set
    VkDescriptorPoolSize poolSize = {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3};
    VkDescriptorPoolCreateInfo poolCreateInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    poolCreateInfo.maxSets = 1;
    poolCreateInfo.poolSizeCount = 1;
    poolCreateInfo.pPoolSizes = &poolSize;
    VkDescriptorPool descriptorPool;
    checkResult(vkCreateDescriptorPool(device, &poolCreateInfo, nullptr, &descriptorPool), "criar descriptor pool");

    VkDescriptorSetAllocateInfo allocInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &descriptorSetLayout;
    VkDescriptorSet descriptorSet;
    checkResult(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet), "alocar DS");

    VkDescriptorBufferInfo bufferInfo[3] = {};
    bufferInfo[0] = {bufferA, 0, sizeA};
    bufferInfo[1] = {bufferB, 0, sizeB};
    bufferInfo[2] = {bufferC, 0, sizeC};
    VkWriteDescriptorSet writes[3] = {};
    for (int i = 0; i < 3; ++i) {
        writes[i] = {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET};
        writes[i].dstSet = descriptorSet;
        writes[i].dstBinding = i;
        writes[i].descriptorCount = 1;
        writes[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        writes[i].pBufferInfo = &bufferInfo[i];
    }
    vkUpdateDescriptorSets(device, 3, writes, 0, nullptr);

    // 12. Command buffer e dispatch
    VkCommandBufferAllocateInfo cmdAlloc = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    cmdAlloc.commandPool = cmdPool;
    cmdAlloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdAlloc.commandBufferCount = 1;
    VkCommandBuffer cmdBuf;
    vkAllocateCommandBuffers(device, &cmdAlloc, &cmdBuf);

    VkCommandBufferBeginInfo beginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cmdBuf, &beginInfo);
    vkCmdBindPipeline(cmdBuf, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    vkCmdBindDescriptorSets(cmdBuf, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
    uint32_t pushData[3] = {M, K, N};
    vkCmdPushConstants(cmdBuf, pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(pushData), pushData);
    uint32_t groupCountX = (N + 15) / 16;
    uint32_t groupCountY = (M + 15) / 16;
    vkCmdDispatch(cmdBuf, groupCountX, groupCountY, 1);
    vkEndCommandBuffer(cmdBuf);

    VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuf;
    VkFence fence;
    VkFenceCreateInfo fenceInfo = {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
    vkCreateFence(device, &fenceInfo, nullptr, &fence);

    // ========== MEDIÇÃO DE TEMPO DA GPU ==========
    auto gpu_start = std::chrono::high_resolution_clock::now();

    vkQueueSubmit(queue, 1, &submitInfo, fence);
    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);

    auto gpu_end = std::chrono::high_resolution_clock::now();
    double gpu_ms = std::chrono::duration<double, std::milli>(gpu_end - gpu_start).count();
    std::cout << "Tempo GPU (submissão + execução): " << gpu_ms << " ms" << std::endl;
    // ============================================

    // 13. Ler resultado da GPU
    std::vector<float> h_C = readBuffer(device, physDevice, queue, cmdPool, bufferC, sizeC);

    // 14. Verificação na CPU com medição de tempo
    std::vector<float> cpu_C(M * N, 0.0f);

    auto cpu_start = std::chrono::high_resolution_clock::now();

    for (uint32_t i = 0; i < M; ++i)
        for (uint32_t j = 0; j < N; ++j)
            for (uint32_t k = 0; k < K; ++k)
                cpu_C[i * N + j] += h_A[i * K + k] * h_B[k * N + j];

    auto cpu_end = std::chrono::high_resolution_clock::now();
    double cpu_ms = std::chrono::duration<double, std::milli>(cpu_end - cpu_start).count();
    std::cout << "Tempo CPU: " << cpu_ms << " ms" << std::endl;

    // Impressão dos resultados (inalterada)
    std::cout << "Resultado GPU (primeiros 5x5):\n";
    for (uint32_t i = 0; i < std::min(M, 5u); ++i) {
        for (uint32_t j = 0; j < std::min(N, 5u); ++j)
            std::cout << h_C[i * N + j] << " ";
        std::cout << "\n";
    }
    std::cout << "Resultado CPU (primeiros 5x5):\n";
    for (uint32_t i = 0; i < std::min(M, 5u); ++i) {
        for (uint32_t j = 0; j < std::min(N, 5u); ++j)
            std::cout << cpu_C[i * N + j] << " ";
        std::cout << "\n";
    }


    // Cleanup
    vkDestroyFence(device, fence, nullptr);
    vkDestroyCommandPool(device, cmdPool, nullptr);
    vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyPipeline(device, pipeline, nullptr);
    vkDestroyShaderModule(device, shaderModule, nullptr);
    vkDestroyBuffer(device, bufferA, nullptr);
    vkDestroyBuffer(device, bufferB, nullptr);
    vkDestroyBuffer(device, bufferC, nullptr);
    vkFreeMemory(device, memA, nullptr);
    vkFreeMemory(device, memB, nullptr);
    vkFreeMemory(device, memC, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);

    return 0;
}