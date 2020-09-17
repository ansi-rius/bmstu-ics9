import javafx.util.Pair;

import java.awt.image.ImageProducer;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class BioinformaticHelper {

    class PairS {
        public String first, second;
    }

    public static void main(String[] args) {

        int vec1_size, vec2_size;

        List<String> lines = new ArrayList<>();
        int line_num = 0;

        try (BufferedReader br = new BufferedReader(new FileReader("/home/dmitry/Ansi_Git_Bio/bmstu-ics9/Bioinformatics/1/src/hugetest.txt"))) {

            while (br.ready()) {
                lines.add(br.readLine());
            }
        } catch (IOException e) {
            System.out.println((e.getMessage()));
        }
        lines.add(">");

        Vector<String> blocks = readLine(lines);
        LinkedHashMap<String, Integer> comb_substing = buildMap(blocks);
        //printMapLine(comb_substing);

        LinkedHashMap<Pair<String, String>, Integer> res = compareBlocks(comb_substing, blocks);

        HashMap<Pair<String, String>, Integer> res_map = compareBlocks2(comb_substing, blocks);


        //printRes(res_map);
        printTable(res_map, blocks);
    }

    public static Vector<String> readLine(List<String> lines) {
        Vector<String> blocks = new Vector<>();
        String str ="";

        for (int i=1; i<lines.size(); i++) {
            if (lines.get(i).substring(0,1).equals(">")) {
                blocks.add(str);
                str = "";
                continue;
            }
            str += lines.get(i);
        }

        //printArray(blocks);
        return blocks;
    }

    public static HashMap<Pair<String, String>, Integer> compareBlocks2(HashMap<String, Integer> comb_substing, Vector<String> blocks) {
        HashMap<Pair<String, String>, Integer> res = new HashMap<>();
        for (int i=0; i<blocks.size(); i++) {
            for (String key : comb_substing.keySet()) {
                if (blocks.get(i).contains(key)) {
                    for (int j=0; j<blocks.size(); j++) {
                        if (blocks.get(j).contains(key)) {
                            Pair<String, String> pair = new Pair<>(blocks.get(i), blocks.get(j));
                            if (!res.containsKey(pair)) {
                                res.put(pair, 1);
                            } else {
                                res.put(pair, res.get(pair)+1);
                            }
                        }
                    }
                }
            }
        }
        return res;
    }

    public static LinkedHashMap<Pair<String, String>, Integer> compareBlocks(LinkedHashMap<String, Integer> comb_substing, Vector<String> blocks) {
        LinkedHashMap<Pair<String, String>, Integer> res = new LinkedHashMap<>();
        for (int i=0; i<blocks.size(); i++) {
            for (String key : comb_substing.keySet()) {
                if (blocks.get(i).contains(key)) {
                    for (int j=0; j<blocks.size(); j++) {
                        if (blocks.get(j).contains(key)) {
                            Pair<String, String> pair = new Pair<>(blocks.get(i), blocks.get(j));
                            if (!res.containsKey(pair)) {
                                res.put(pair, 1);
                            } else {
                                res.put(pair, res.get(pair)+1);
                            }
                        }
                    }
                }
            }
        }
        return res;
    }

    public static LinkedHashMap<String, Integer> buildMap(Vector<String> blocks) {
        LinkedHashMap<String, Integer> comb_substing = new LinkedHashMap<String, Integer>();
        int cut = 3;
        for (int i=0; i<blocks.size(); i++) {
            for (int j=0; j<blocks.get(i).length()-cut; j++) {
                String cut_str = blocks.get(i).substring(j,j+cut);
                if (!comb_substing.containsKey(cut_str)) {
                    comb_substing.put(cut_str, 1);
                } else {
                    comb_substing.put(cut_str, comb_substing.get(cut_str)+1);
                }
            }
        }
        return comb_substing;
    }

    public static void printArray(List<String> arr) {
        System.out.println("Arr print started:");
        for (int i=0; i<arr.size(); i++) {
            System.out.println("    ["+i+"]"+arr.get(i));
        }
        System.out.println("Arr print ended.");
    }

    public static void printMapLine(LinkedHashMap<String, Integer> comb_substing) {

        Set<Map.Entry<String, Integer>> mapSet = comb_substing.entrySet();
        List<Map.Entry<String, Integer>> mapListEntry = new ArrayList<Map.Entry<String, Integer>>(mapSet);
        Collections.sort(mapListEntry, new Comparator<Map.Entry<String, Integer>>() {
            @Override
            public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                return o1.getValue().compareTo(o2.getValue());
            }
        });
        comb_substing.clear();
        for (Map.Entry<String, Integer> map : mapListEntry) {
            comb_substing.put(map.getKey(), map.getValue());
        }

        System.out.println("Map print started:");
        for (String key : comb_substing.keySet()) {
            System.out.println("    "+ key +" : "+ comb_substing.get(key));
        }

        System.out.println("Map print ended.");
    }

    public static void printRes(HashMap<Pair<String, String>, Integer> res) {
        System.out.println("Res print started:");
        int max = 0;
        for (Map.Entry entry : res.entrySet()) {
            //System.out.println("    "+ entry.getKey() +" : "+ entry.getValue());
            if ((int)entry.getValue()>=max) {
                max = (int)entry.getValue();
            }
        }
  /*      for (Map.Entry entry : res.entrySet()) {
            System.out.print("    "+ entry.getKey() +" : ");
            System.out.printf("%.3f", (double)((int)entry.getValue())/max*100);
            System.out.println("%");
        }
*/      int a = 0;
        try(FileWriter writer = new FileWriter("outp.txt", false))
        {
            // запись всей строки

            for (Map.Entry entry : res.entrySet()) {
                a = a + 1; //count iter
                double f = (double)((int)entry.getValue())/max*100;
                String text = "    "+ entry.getKey() +" : "+ f + "%";
                writer.write(text);

            }

            writer.flush();
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }





        System.out.println("Res print ended." + a);
    }

    public static void printTable(HashMap<Pair<String, String>, Integer> res, Vector<String> blocks) {
        String table[] = new String[69*69];

        for (int i = 0; i <69*69; i++) {
            table[i] = "0";
        }

        int max = 0;
        for (Map.Entry entry : res.entrySet()) {
            //System.out.println("    "+ entry.getKey() +" : "+ entry.getValue());
            if ((int)entry.getValue()>=max) {
                max = (int)entry.getValue();
            }
        }/*
            0 1 2  3
            4 5 6  7
            8 9 10 11

        */
        for (int i = 0; i < blocks.size(); i++) {
            for (int j = 0; j < blocks.size(); j++) {
                for (Map.Entry entry : res.entrySet()) {
                    String key_ex = blocks.get(i)+"="+blocks.get(j);
                    if (entry.getKey().toString().equals(key_ex)){
                        System.out.print("Work on i = " + i + " j = " + j);
                        double f = (double)((int)entry.getValue())/max*100;
                        table[i * 69 + j] = f+"%";
                        System.out.println(" value : " + table[i * 69 + j]);

                    }
                }
            }
        }
        try(FileWriter writer = new FileWriter("table.txt", false))
        {
            // запись таблицы
            int k = 69*69;
            String str = "";
            for (int i = 0; i < k; i++) {
                if (i % 69 == 0){
                    writer.write(str);
                    str = "";
                }
                if (!table[i].equals("0")) {
                    str += "      " + table[i].substring(0, 4) + "%";
                }else{
                    str += "      " + table[i] + "%   ";
                }
            }

            writer.flush();
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }



    }


}


