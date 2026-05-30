#ifndef LINEAR_TRANSFORMATION_H
#define LINEAR_TRANSFORMATION_H

#include "AbstractTransformation.h"
#include <array>

template <typename ScalarType, int lines, int collums>
class LinearTransformation : public AbstractTransformation<ScalarType, lines, collums> {


    const std::array<ScalarType, lines * collums> components;

    public:

      static_assert(lines > 0, "Input Dimension must be greater than 0");

    static_assert(collums > 0, "Output Dimension must be greater than 0");




    ScalarType getComponent(const int& line, const int& collum) {
        return components[collum + line * collums];
    }

    int getLines() {
        return lines;
    }

    int getCollums() {
        return collums;
    }

    LinearTransformation<ScalarType, lines, collums> operator+(const LinearTransformation<ScalarType, lines, collums>& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator+=(const LinearTransformation<ScalarType, lines, collums>& other) {
        
    }

    LinearTransformation<ScalarType, lines, collums> operator-(const LinearTransformation<ScalarType, lines, collums>& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator-=(const LinearTransformation<ScalarType, lines, collums>& other) {
        
    }

    LinearTransformation<ScalarType, lines, collums> operator*(const LinearTransformation<ScalarType, lines, collums>& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator*=(const LinearTransformation<ScalarType, lines, collums>& other) {
        
    }

    LinearTransformation<ScalarType, lines, collums> operator/(const LinearTransformation<ScalarType, lines, collums>& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator/=(const LinearTransformation<ScalarType, lines, collums>& other) {
        
    }

    LinearTransformation<ScalarType, lines, collums> operator*(const ScalarType& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator*=(const ScalarType& other) {
        
    }

      LinearTransformation<ScalarType, lines, collums> operator/(const ScalarType& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums>& operator/=(const ScalarType& other) {
        
    }

    AbstractVector<lines, ScalarType> operator*(const AbstractVector<collums, ScalarType>& other) const {
        
    }

    LinearTransformation<ScalarType, lines, collums> inverse() const {

    }

    bool isOrthonormal() const {

    }

    double getDet() const {
        
    }

    ScalarType getEigenValues(){

    }

    LinearTransformation<ScalarType,  lines,  collums> exp(const ScalarType& value){
        
    }

    std::array<AbstractVector<lines, ScalarType>, collums> getEigenvectors(){

    }
    std::array<AbstractVector<lines, ScalarType>, collums> getBasis() const{

    }

     std::array<AbstractVector<lines, ScalarType>, collums> getImg() const{

    }

     std::array<AbstractVector<lines, ScalarType>, collums> getKernel() const{

    }

    int getRank() const {
        
    }

    int getNullity() const {
        
    }






   
    








};


#endif