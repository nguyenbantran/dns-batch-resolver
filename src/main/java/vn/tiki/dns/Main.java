package vn.tiki.dns;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Main {

    static Map<String, String> maps = new HashMap<>();

    public static void main(String[] args) throws Exception {
        loadAllLine();
        for (var x : maps.keySet()) {
            System.out.println("'" + x + "'");
        }
    }

    private static void loadAllLine() throws Exception {
        // Open the file
        FileInputStream fstream = new FileInputStream("opendns-top-domains.txt");
        BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

        String strLine;

        //Read File Line By Line
        while ((strLine = br.readLine()) != null)   {
            maps.put(strLine.trim(), "");
        }

        // Close the input stream
        fstream.close();
    }
}
