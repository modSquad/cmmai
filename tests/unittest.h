
 #define cmmai_assert(message, test) do { if (!(test)) return message; } while (0)
 #define cmmai_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;
