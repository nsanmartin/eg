%x comment
%%
        int line_num = 1;

"/*"         BEGIN(comment);

\/\/.*\n				/* ignore c++ commnents */
<comment>[^*]*			/* eat anything that's not a '*' */
<comment>"*"+[^*/]*		/* eat up '*'s not followed by '/'s */
<comment>"*"+"/"		BEGIN(INITIAL);
