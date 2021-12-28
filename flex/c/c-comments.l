%x comment
%%
"/*"         BEGIN(comment);

<comment>[^*]*			/* eat anything that's not a '*' */
<comment>"*"+[^*/]*		/* eat up '*'s not followed by '/'s */
<comment>"*"+"/"		BEGIN(INITIAL);
