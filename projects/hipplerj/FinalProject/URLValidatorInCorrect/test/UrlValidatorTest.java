import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

    public UrlValidatorTest(String testName) {
        super(testName);
    }

    public void testManualTest() {
        UrlValidator UrlValidator = new UrlValidator();

        String[] correctUrls = new String[10];
        correctUrls[0] = "http://www.google.com";
        correctUrls[1] = "https://www.google.com";
        correctUrls[2] = "http://www.google.com/";
        correctUrls[3] = "https://oregonstate.edu";
        correctUrls[4] = "https://careers.google.com/locations/";
        correctUrls[5] = "https://www.oregon.gov/pages/index.aspx";
        correctUrls[6] = "http://www.google.com:80";
        correctUrls[7] = "172.217.8.174";
        correctUrls[8] = "https://www.google.com/search?q=recursion";
        correctUrls[9] = "ftp://www.google.com";

        String[] wrongUrls = new String[7];
        wrongUrls[0] = "http:/www.google.com";
        wrongUrls[1] = "http://www.google.com/locations//testing/";
        wrongUrls[2] = "256.256.256.256";
        wrongUrls[3] = "http://www.google.com:-1";
        wrongUrls[4] = "http://www..com";
        wrongUrls[5] = "www.google.com";
        wrongUrls[6] = "fail://www.google.com";

        System.out.println(UrlValidator.isValid("http://www.google.com"));

        System.out.println("These should PASS:");
        for (int i = 0; i < correctUrls.length; i++) {
            softEvaluate(UrlValidator.isValid(correctUrls[i]), correctUrls[i]);
        }

        System.out.println("These should FAIL:");
        for (int i = 0; i < wrongUrls.length; i++) {
            softEvaluate(UrlValidator.isValid(wrongUrls[i]), wrongUrls[i]);
        }
    }

    public void softEvaluate(boolean pass, String tested) {
        if (pass) {
            System.out.println("PASSED -" + tested + " - URL is valid.");
        } else {
            System.out.println("FAILED - " + tested + " - URL is invalid.");
        }
    }

    public void test_url_schemes() {
        String name = "Schemes";
        String[] schemes = { "https://", "http://", "ftp://", "http/", "http:", "://", "" };
        Boolean[] validity = { true, true, true, false, false, false, true };
        System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL SCHEMES" +
                "\u001B[0m");
        perform_partition_test(name, schemes, validity);
    }

    public void test_url_authority() {
        String name = "Authority";
        String[] authority = { "www.oregonstate.edu", "www.google.com", "www.reddit.com", "www.boisestate.bad",
                               "bad.apple.com", "bad.archlinux.bad", "www..stackoverflow.com", "www.utexas..com",
                               "www.texas.gov", "www.wikipedia.org" };
        Boolean[] validity = { true, true, true, false, false, false, false, false, true, true };
        System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL AUTHORITY" + "\u001B[0m");
        perform_partition_test(name, authority, validity);
    }

    public void test_url_port() {
        String name = "Port";
        String[] port = { "www.oregonstate.edu:80", "www.oregonstate.edu:0", "www.oregonstate.edu:-1",
                          "www.oregonstate.edu:65535", "www.oregonstate.edu:65536", "www.oregonstate.edu:7777",
                          "www.oregonstate.edu:77777", "www.oregonstate.edu:77c", "www.oregonstate.edu:" };
        Boolean[] validity = { true, true, false, true, false, true, false, false, true };
        System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PORT" + "\u001B[0m");
        perform_partition_test(name, port, validity);
    }

    public void test_url_path() {
        String name = "Path";
        String[] path = { "/path", "/..", "/path/", "/path1/path2", "/../", "/$path", "/..//path" };
        Boolean[] validity = { true, false, true, false, false, true, false };
        System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PATH" +
                "\u001B[0m");
        perform_partition_test(name, path, validity);
    }

    public void test_url_query() {
        String name = "Query";
        String[] query = { "?action=view", "?action=edit&mode=up", "" };
        Boolean[] validity = { true, true, true };
        System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL QUERY" +
                "\u001B[0m");
        perform_partition_test(name, query, validity);
    }

    private void perform_partition_test(String name, String[] partition, Boolean[] validity) {
        boolean check;
        UrlValidator validate_part = new UrlValidator(partition, UrlValidator.ALLOW_ALL_SCHEMES);
        for (int i = 0; i < partition.length; i++) {
            System.out.println("Testing " + name + ": \"" + partition[i] + "\"");
            if(name.equals("Schemes")) {
                check = validate_part.isValidScheme(partition[i]);
            } else {
                check = validate_part.isValid(partition[i]);
            }
            System.out.println("UrlValidator " + name + " Value: " + check);
            System.out.println("Actual " + name + " Value: " + validity[i]);
            if (check != validity[i]) {
                System.out.println("[" + "\u001B[31m" + "FAILED" + "\u001B[0m" +
                        "] URLValidator Return INCORRECT " + name + " Results\n");
            } else {
                System.out.println("[" + "\u001B[32m" + "PASSED" + "\u001B[0m" +
                        "] URLValidator Return CORRECT " + name + " Results\n");
            }
        }
    }

    public void test_random_url() {
        UrlValidator validate_part = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Boolean overall_valid = true;
        Boolean check;
        String URL;
        String base_URL = "oregonstate";
        Random rand = new Random();
        int[] length = { 6, 1, 1, 8, 6, 2};
        int[] random_numbers = { 0, 0, 0, 0, 0, 0};
        Boolean[] validator = { false, false, false, false, false, true };
        String[] schemes = { "https://", "http://", "ftp://", "",       // Valid Schemes
                             "http/", "http:", "://" };                 // Invalid Schemes
        String[] start_authority = { "www.",                            // Valid Starting Authority
                                     "bad." };                          // Invalid Starting Authority
        String[] ending_authority = { ".com", ".edu", ".gov", ".org",   // Valid Ending Authority
                                      ".bad"};                          // Invalid Ending Authority
        String[] port = {":80", ":0", ":65535", ":7777", "",             // Valid Ports
                         ":-1", ":65536" , ":77777", ":77c" };          // Invalid Ports
        String[] path = {"/path", "/path/", "/$path",                   // Valid Paths
                         "/path1/path2", "/../", "/..//path", "/.."};   // Invalid Paths
        String[] query = {"?action=view", "?action=edit&mode=up", ""};  // Valid Queries

        for (int tests = 0; tests < 5000; tests ++) {
            for (int i = 0; i < 6; i++) {
                random_numbers[i] = rand.nextInt(length[i]);
            }
            URL = schemes[random_numbers[0]] + start_authority[random_numbers[1]] + base_URL +
                    ending_authority[random_numbers[2]] + port[random_numbers[3]] + path[random_numbers[4]] +
                    query[random_numbers[5]];

            if (random_numbers[0] <= 3) {
                validator[0] = true;
            } else {
                validator[0] = false;
                overall_valid = false;
            }
            if (random_numbers[1] == 0) {
                validator[1] = true;
            } else {
                validator[1] = false;
                overall_valid = false;
            }
            if (random_numbers[2] <= 3) {
                validator[2] = true;
            } else {
                validator[2] = false;
                overall_valid = false;
            }
            if (random_numbers[3] <= 4) {
                validator[3] = true;
            } else {
                validator[3] = false;
                overall_valid = false;
            }
            if (random_numbers[4] <= 2) {
                validator[4] = true;
            } else {
                validator[4] = false;
                overall_valid = false;
            }
            check = validate_part.isValidScheme(URL);
            System.out.println("Random URL Test " + (tests + 1));
            System.out.println("Randomized URL: " + URL);
            System.out.println("Returned URL Validity: " + check);
            System.out.println("URL Actual Validity: " + overall_valid);
            if ((overall_valid && check) || (!overall_valid && !check)) {
                System.out.println("[" + "\u001B[32m" + "PASSED" + "\u001B[0m" +
                        "] URL successfully validated\n");
            } else {
                System.out.println("[" + "\u001B[31m" + "FAILED" + "\u001B[0m" +
                        "] URL unsuccessfully validated\n");
            }
        }
    }
}

