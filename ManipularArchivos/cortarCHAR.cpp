    /* strtok example */
    #include <stdio.h>
    #include <string.h>

    int main ()
    {
      char str[] = "- This,) a sample( string.";
      char * pch;
      printf ("Splitting string \"%s\" into tokens:\n",str);
      pch = strtok (str," ,.-()");   // Aqui deja solo la coma
      while (pch != NULL)
      {
        printf ("%s\n",pch);     // Aqui deberias guardar tu dato en el array!
        pch = strtok (NULL, " ,.-()");  // Aca tambien iria solo la coma.!!
      }
      return 0;
    }
