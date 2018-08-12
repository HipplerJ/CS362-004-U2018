import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest() {
     //You can use this function to implement your manual testing
   }

   // JAMES HIPPLER (HIPPLERJ)
   public void test_url_schemes() {
       String name = "Schemes";
       String[] schemes = { "https://", "http://", "ftp://", "http/", "h3t://", "http:", "://", "" };
       Boolean[] validity = { true, true, true, false, true, false, false, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL SCHEMES" + "\u001B[0m");
       perform_partition_test(name, schemes, validity);
   }

   public void test_url_authority() {
       String name = "Authority";
       String[] authority = { "www.oregonstate.edu", "www.google.com", "www.reddit.com", "www.boisestate.bad", "bad.apple.com", "bad.archlinux.bad",
                            "256.256.256.256", "256.256.256.256" };
       Boolean[] validity = { true, true, true, false, false, false, true, false };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL AUTHORITY" + "\u001B[0m");
       perform_partition_test(name, authority, validity);
   }

   public void test_url_port() {
       String name = "Port";
       String[] port = { "www.oregonstate.edu:80", "www.oregonstate.edu:7777", "www.oregonstate.edu:-1", "www.oregonstate.edu:77c",
                         "www.oregonstate.edu:", "www.oregonstate.edu:65636", "www.oregonstate.edu:65535" };
       Boolean[] validity = { true, true, false, false, true, false, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PORT" + "\u001B[0m");
       perform_partition_test(name, port, validity);
   }

   public void test_url_path() {
       String name = "Path";
       String[] path = { "/path", "/..", "/path/", "/path1//path2", "/../", "/$path", "/..//path" };
       Boolean[] validity = { true, false, true, false, false, true, false };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL PATH" + "\u001B[0m");
       perform_partition_test(name, path, validity);
   }

   public void test_url_query() {
       String name = "Query";
       String[] authority = { "?action=view", "?action=edit&mode=up", "" };
       Boolean[] validity = { true, true, true };
       System.out.println("PARTITION TESTING: " + "\u001B[34m" + "URL QUERY" + "\u001B[0m");
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
               System.out.println("[" + "\u001B[31m" + "FAILED" + "\u001B[0m" + "] URLValidator Return INCORRECT " + name + " Results\n");
           } else {
               System.out.println("[" + "\u001B[32m" + "PASSED" + "\u001B[0m" + "] URLValidator Return CORRECT " + name + " Results\n");
           }
       }
   }

   //You need to create more test cases for your Partitions if you need to

   public void testIsValid() {
	   //You can use this function for programming based testing
   }
}
