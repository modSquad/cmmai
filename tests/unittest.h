
/**
 * Voici ce que j'utilisais en DUT, c'est un microframework de test pour C.
 * Voir : http://www.jera.com/techinfo/jtns/jtn002.html
 */


/* Utiliser en lieu et place d'une assert */
 #define cmmai_assert(message, test) do { if (!(test)) return message; } while (0)
/* Lance le test de nom "test", qui doit être une fonction */
 #define cmmai_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;
