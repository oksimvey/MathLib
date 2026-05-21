
public class Animal {
    

    final AnimalsEnum animalEnum;

    public Animal(AnimalsEnum animalEnum) {
        this.animalEnum = animalEnum;
    }

    public void makeSound() {
        System.out.println(animalEnum.sound);
    }
}
