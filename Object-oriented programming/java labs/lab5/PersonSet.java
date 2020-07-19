import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

class PersonSet {
    private HashSet<PersonSet> pers;

    public PersonSet() {
        pers = new HashSet<>();
    }

   /* public Stream<String> getName() {
        return Arrays.stream("a b c".split(" ",2));
    }*/


   public Stream<String> getName() {
       pers.stream()
               .forEach(i -> setlist(i));

   }

   public  setlist(String a) {

   }

    //public Optional<Person> getOldestPersonbySurname() {
//
    //}

    public Optional<String> getMostRepeatedName() {
        ArrayList<String> names = pers.stream().map(PersonSet::getName)
                .collect(Collectors.toCollection(ArrayList::new));
        return names.stream()
                .max(Comparator.comparing(bi -> names.stream()
                                                .mapToInt(c -> c.equals(bi) ? 1 : 0).sum()));
    }


    public int size() {
        return pers.size();
    }

}