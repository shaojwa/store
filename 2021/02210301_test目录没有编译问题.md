```
--- a/src/CMakeLists.txt
+++ b/src/CMakeLists.txt
@@ -1054,7 +1054,7 @@ add_subdirectory(erasure-code)
 # Support/Tools
 if(WITH_TESTS)
 add_subdirectory(googletest/googlemock)
-#add_subdirectory(test)
+add_subdirectory(test)
 endif(WITH_TESTS)
```
