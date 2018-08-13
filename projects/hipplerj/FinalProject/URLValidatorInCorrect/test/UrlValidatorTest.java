import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   // KYLE MARTINEZ (MARTINK9)
   public void testManualTest() {
     //You can use this function to implement your manual testing
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

   // JAMES HIPPLER (HIPPLERJ)
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
       String[] authority = { "www.oregonstate.edu","www.google.com","www.reddit.com","www.boisestate.bad",
                              "bad.apple.com","bad.archlinux.bad","www..stackoverflow.com","www.utexas..com",
                              "www.texas.gov","www.wikipedia.org" };
       Boolean[] validity = { true, true, true, false, false, false, false, false, true, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL AUTHORITY" +
       "\u001B[0m");
       perform_partition_test(name, authority, validity);
   }

   public void test_url_port() {
       String name = "Port";
       String[] port = { ":80",":0",":-1","65535","65536","7777","77777",":77c","" };
       Boolean[] validity = { true, true, false, true, false, true, false, false, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PORT" +
       "\u001B[0m");
       perform_partition_test(name, port, validity);
   }

   public void test_url_path() {
       String name = "Path";
       String[] path = {    "/path","/..","/path/","/path1/path2","/../","/$path","/..//path" };
       Boolean[] validity = { true, false, true, false, false, true, false };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PATH" +
       "\u001B[0m");
       perform_partition_test(name, path, validity);
   }

   public void test_url_query() {
       String name = "Query";
       String[] authority = { "?action=view", "?action=edit&mode=up", "" };
       Boolean[] validity = { true, true, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL QUERY" +
       "\u001B[0m");
       perform_partition_test(name, authority, validity);
   }

   private void perform_partition_test(String name, String[] partition, Boolean[] validity) {
       boolean check;
       UrlValidator validate_scheme = new UrlValidator(partition, UrlValidator.ALLOW_ALL_SCHEMES);
       for (int i = 0; i < partition.length; i ++) {
           System.out.println("Testing " + name + ": \"" + partition[i] + "\"");
           check = validate_scheme.isValidScheme(partition[i]);
           System.out.println("UrlValidator " + name + " Value: " + check);
           System.out.println("Actual " + name + " Value: " + validity[i]);
           if(check != validity[i]){
               System.out.println("[" + "\u001B[31m" + "FAILED" + "\u001B[0m" +
               "] URLValidator Return INCORRECT " + name + " Results\n");
           } else {
               System.out.println("[" + "\u001B[32m" + "PASSED" + "\u001B[0m" +
               "] URLValidator Return CORRECT " + name + " Results\n");
           }
       }
   }

   //You need to create more test cases for your Partitions if you need to

   public void testIsValid() {
	   //You can use this function for programming based testing
   }
}
