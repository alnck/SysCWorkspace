/*------------------------------------------------------------------------------------------------------------------------------------------
	strtok Fonksiyonun Kullanımı (1)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "  Ali,    Veli, Selami   ";
	char *pstr;

	pstr = strtok(s, ", ");
	while (pstr != NULL) {
		puts(pstr);
		pstr = strtok(NULL, ", ");
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	strtok Fonksiyonun Kullanımı (2)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "  Ali,    Veli, Selami   ";
	char *pstr;

	for (pstr = strtok(s, ", "); pstr != NULL; pstr = strtok(NULL, ", "))
		puts(pstr);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	strtok Fonksiyonun Kullanımı (3)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "12/11/2009";
	char *pstr;

	for (pstr = strtok(s, "/"); pstr != NULL; pstr = strtok(NULL, "/"))
		puts(pstr);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	strtok Fonksiyonunun birinci parametresiyle aldığı adreste değişiklik yaptığına dikkat ediniz. Bu nedenle aşağıdaki kod
	tanımsız davranışa yol açacaktır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = "12/11/2009";
	char *pstr;

	for (pstr = strtok(s, "/"); pstr != NULL; pstr = strtok(NULL, "/"))
		puts(pstr);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Microsoft derleyicilerinde strtok fonksiyonun strtok_s ismiyle thread güvenli bir versiyonu da vardır.Microsoft'un strtok_s fonksiyonun tamamen 
	eşdeğeri GNU C kütüphanesinde strtok_r ismindedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "12/11/2009";
	char *pstr;
	char *pstrl;

	for (pstr = strtok_s(s, "/", &pstrl); pstr; pstr = strtok_s(NULL, "/", &pstrl))
		puts(pstr);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	strtok fonksiyonun gerçekleştirimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

char *mystrtok(char *str, const cha *delim)
{
	static char *pos;
	char *beg;

	if (str != NULL)
		pos = str;

	while (*pos != '\0' && strchr(delim, *pos) != NULL)
		++pos;

	if (*pos == '\0')
		return NULL;

	beg = pos;

	while (*pos != '\0' && strchr(delim, *pos) == NULL)
		++pos;

	if (*pos != '\0')
		*pos++ = '\0';

	return beg;
}

int main(void)
{
	char s[] = "";
	char *pstr;

	for (pstr = mystrtok(s, ","); pstr != NULL; pstr = mystrtok(NULL, ","))
		puts(pstr);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	strtok fonksiyonun birinci parametrenin const olan (yani birinci parametresindeki yazıyı değiştirmeyen) versyionu
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

char *mystrtok(const char *str, const char *delim, char *dest)
{
	static const char *pos;
	const char *beg;

	if (str != NULL)
		pos = str;

	while (*pos != '\0' && strchr(delim, *pos) != NULL)
		++pos;

	if (*pos == '\0')
		return NULL;

	beg = pos;

	while (*pos != '\0' && strchr(delim, *pos) == NULL)
		++pos;

	strncpy(dest, beg, pos - beg);
	dest[pos - beg] = '\0';

	return dest;
}

int main(void)
{
	char text[] = "10/12/2009";
	char str[100];
	char *pstr;

	for (pstr = mystrtok(text, "/", str); pstr != NULL; pstr = mystrtok(NULL, "/", str))
		puts(pstr);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	strtok fonksiyonun dinamik bir alan tahsis edip o alana gerei dönen versyionu. Ancak burada fonksiyon kullanan kişinin bu alanı kendisinin 
	free etmesi gerekir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrtok(const char *str, const char *delim)
{
	static const char *pos;
	const char *beg;
	char *dstr;

	if (str != NULL)
		pos = str;

	while (*pos != '\0' && strchr(delim, *pos) != NULL)
		++pos;

	if (*pos == '\0')
		return NULL;

	beg = pos;

	while (*pos != '\0' && strchr(delim, *pos) == NULL)
		++pos;

	if ((dstr = (char *)malloc(pos - beg + 1)) == NULL)
		return NULL;

	strncpy(dstr, beg, pos - beg);
	dstr[pos - beg] = '\0';

	return dstr;
}

int main(void)
{
	char text[] = "10/12/2009";
	char *pstr;

	for (pstr = mystrtok(text, "/"); pstr != NULL; pstr = mystrtok(NULL, "/")) {
		puts(pstr);
		free(pstr);
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Bir dosyayı satır satır okuyarak her satırı strok fonksiyonuyla atomlarına ayrıştırabiliriz. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE		4096

int main(void)
{
	FILE *f;
	char line[MAX_LINE];
	char *str;

	if ((f = fopen("test.csv", "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, MAX_LINE, f) != NULL) {
		if ((str = strchr(line, '\n')) != NULL)
			*str = '\0';

		for (str = strtok(line, ","); str != NULL; str = strtok(NULL, ","))
			printf("%s ", str);
		printf("\n");
	}

	fclose(f);

	return 0;
}

/* test.csv */

Ali Serçe, 100, 200, 300
Sacit Bulut, 12.3, 56.3, 78.2
Hakan Akyıldız, 12.3, 67.3
Hüsnü Biter, 12, 34, 34

/* ------------------------------------------------------------------------------------------------------------------------------------------
	remove standart bir C fonksiyonudur. Başarı durumunda 0 değerine başarısızlık durumunda sıfır dışı bir değere geri döner.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	if (remove("test.txt") != 0) {
		fprintf(stderr, "cannot remove file!..\n");
		exit(EXIT_FAILURE);
	}

	printf("success..\n");

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	system fonksiyonu ilgili sistemdeki "komut yorumlayıcı (command interpreter)" programını çalıştırır ve argüman olarak girilen komutu işletir.
	C standartlarına göre fonksiyonun geri dönüş derleyicilerin isteklerine bırakılmıştır (implementation dependent). Ancak Windows ve UNIX/Linux
	sistemleri başarı durumunda 0, başarısızlık durumunda sıfır dışı bir değere geri dönmektedir. Bu konun ayrıntıları ileride ele alınacaktır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	system("ls -l");

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	tmpfile isimli standart C fonksiyonu olmayan bir dosya ismi ile bir dosyayı "w+b" modunda yaratır ve dosyaya ilişkin dosya bilgi göstericisiyle
	geri döner. Böyle dosyalar kapatıldığında diskteki dosyada otomatik olarak silinecektir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *f;
	int i, val;

	if ((f = tmpfile()) == NULL) {
		fprintf(stderr, "cannot create temporary file!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 100; ++i)
		if (fwrite(&i, sizeof(int), 1, f) != 1) {
			fprintf(stderr, "cannot write file!..\n");
			exit(EXIT_FAILURE);
		}

	fseek(f, 0, SEEK_SET);

	while (fread(&val, sizeof(int), 1, f) > 0)
		printf("%d\n", val);

	if (ferror(f)) {
		fprintf(stderr, "cannot read file!..\n");
		exit(EXIT_FAILURE);
	}

	fclose(f);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Bir dosyadaki # ile başlayan satırları silen program örneği. Programın tek bir komut satırı argümanı vardır. O da #'lerden arındırılacak dosyanın
	yol ifadesini belirtir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE		8192

int issharp(const char *line);

int main(int argc, char *argv[])
{
	FILE *f, *ftemp;
	char line[MAX_LINE];
	char *path;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((path = tmpnam(NULL)) == NULL) {
		fprintf(stderr, "cannot get temporary file!..\n");
		exit(EXIT_FAILURE);
	}

	if ((f = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	if ((ftemp = fopen(path, "w")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, MAX_LINE, f) != NULL) {
		if (!issharp(line))
			if (fputs(line, ftemp) == EOF) {
				fprintf(stderr, "cannot write file temporary file!..\n");
				goto FAILURE;
			}
	}

	if (ferror(f)) {
		fprintf(stderr, "cannot read file: %s\n", argv[1]);
		goto FAILURE;
	}

	fclose(f);
	fclose(ftemp);

	if (remove(argv[1]) != 0) {
		fprintf(stderr, "cannot remove file!..\n");
		goto FAILURE;
	}

	if (rename(path, argv[1]) != 0) {
		fprintf(stderr, "cannot rename file!..\n");
		exit(EXIT_FAILURE);
	}

	printf("sucess...\n");

	exit(EXIT_SUCCESS);

FAILURE:
	fclose(ftemp);
	if (remove(path) != 0)
		fprintf(stderr, "cannot remove file!..\n");

	exit(EXIT_FAILURE);

	return 0;
}

int issharp(const char *line)
{
	while (isspace(*line))
		++line;

	return *line == '#';
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	getopt fonksiyonun kullanımı. Seçenkler argümanlar için argüman optrag global değişneinin gösterdiği adrestedir. Seçeneksiz argümanlar
	komut satırı argümanlarının sonuna alınır ve opting global değişkeni seçeneksiz argümanların başladığı yeri gösterir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int result;
	int a_flag, b_flag, c_flag;
	char *b_arg;
	int i;

	a_flag = b_flag = c_flag = 0;

	while ((result = getopt(argc, argv, "ab:c")) != -1) {
		switch (result) {
		case 'a':
			a_flag = 1;
			break;
		case 'b':
			b_flag = 1;
			b_arg = optarg;
			break;
		case 'c':
			c_flag = 1;
			break;
		}
	}

	if (a_flag)
		printf("-a option used...\n");

	if (b_flag)
		printf("-b option used with argument \"%s\"...\n", b_arg);

	if (c_flag)
		printf("-c option used...\n");

	if (c_flag)
		printf("-c option used...\n");

	if (optind != argc) {
		printf("Seçeneksiz (yani normal) argümanlar:\n");
		for (i = optind; i < argc; ++i)
			printf("%s\n", argv[i]);
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	getopt fonksiyonun kullanımına örnek 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int result;
	int a_flag, b_flag, c_flag;
	char *b_arg;
	int i, err_flag;

	opterr = 0;
	a_flag = b_flag = c_flag = 0;
	err_flag = 0;

	while ((result = getopt(argc, argv, "ab:c")) != -1) {
		switch (result) {
		case 'a':
			a_flag = 1;
			break;
		case 'b':
			b_flag = 1;
			b_arg = optarg;
			break;
		case 'c':
			c_flag = 1;
			break;
		case '?':
			if (optopt == 'b')
				fprintf(stderr, "-b option must have an argument!..\n");
			else
				fprintf(stderr, "invalid option: -%c\n", optopt);
			err_flag = 1;
			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (a_flag)
		printf("-a option used...\n");

	if (b_flag)
		printf("-b option used with argument \"%s\"...\n", b_arg);

	if (c_flag)
		printf("-c option used...\n");

	if (c_flag)
		printf("-c option used...\n");

	if (optind != argc) {
		printf("Seçeneksiz (yani normal) argümanlar:\n");
		for (i = optind; i < argc; ++i)
			printf("%s\n", argv[i]);
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	getopt kullanımına bir örnek

	./mycalc [-asmd] <number1> <number2>
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* mycalc.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int result;
	int a_flag, s_flag, m_flag, d_flag;
	int err_flag;
	double arg1, arg2, val_result;

	opterr = 0;

	a_flag = s_flag = m_flag = d_flag = 0;
	err_flag = 0;

	while ((result = getopt(argc, argv, "asmd")) != -1) {
		switch (result) {
		case 'a':
			a_flag = 1;
			break;
		case 's':
			s_flag = 1;
			break;
		case 'm':
			m_flag = 1;
			break;
		case 'd':
			d_flag = 1;
			break;
		case '?':
			fprintf(stderr, "invalid option: -%c\n", optopt);
			err_flag = 1;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (a_flag + s_flag + m_flag + d_flag != 1) {
		fprintf(stderr, "exactly one option must be specified!..\n");
		exit(EXIT_FAILURE);
	}

	if (argc - optind != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	arg1 = strtod(argv[optind], NULL);
	arg2 = strtod(argv[optind + 1], NULL);

	if (a_flag)
		val_result = arg1 + arg2;
	else if (s_flag)
		val_result = arg1 - arg2;
	else if (m_flag)
		val_result = arg1 * arg2;
	else
		val_result = arg1 / arg2;

	printf("%f\n", val_result);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	getopt_long fonksiyonun kullanımına bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int result;
	int a_flag, b_flag, c_flag, help_flag, count_flag, line_flag;
	char *b_arg, *count_arg, *line_arg;
	int err_flag;
	int i;

	struct option options[] = {
		{"help", no_argument, &help_flag, 1},
		{"count", required_argument, NULL, 2},
		{"line", optional_argument, NULL, 3},
		{0, 0, 0, 0 },
	};

	opterr = 0;

	a_flag = b_flag = c_flag = help_flag = count_flag = line_flag = 0;
	err_flag = 0;

	while ((result = getopt_long(argc, argv, "ab:c", options, NULL)) != -1) {
		switch (result) {
		case 'a':
			a_flag = 1;
			break;
		case 'b':
			b_flag = 1;
			b_arg = optarg;
			break;
		case 'c':
			c_flag = 1;
			break;
		case 2:			/* --count */
			count_flag = 1;
			count_arg = optarg;
			break;
		case 3:			/* --line */
			line_flag = 1;
			line_arg = optarg;
			break;
		case '?':
			if (optopt == 'b')
				fprintf(stderr, "-b option must have an argument!..\n");
			else if (optopt == 2)
				fprintf(stderr, "argument must be specified with --count option\n");
			else if (optopt != 0)
				fprintf(stderr, "invalid option: -%c\n", optopt);
			else
				fprintf(stderr, "invalid long option!..\n");

			err_flag = 1;

			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (a_flag)
		printf("-a option used...\n");

	if (b_flag)
		printf("-b option used with argument \"%s\"...\n", b_arg);

	if (c_flag)
		printf("-c option used...\n");

	if (help_flag)
		printf("--help option used...\n");

	if (count_flag)
		printf("--count option specified with \"%s\"...\n", count_arg);

	if (line_flag) {
		if (line_arg != NULL)
			printf("--line option used with optional argument \"%s\"\n", line_arg);
		else
			printf("--line option used without optional argument...\n");
	}

	if (optind != argc) {
		printf("Seçeneksiz (yani normal) argümanlar:\n");
		for (i = optind; i < argc; ++i)
			printf("%s\n", argv[i]);
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	getopt_long örneği (Bazen kısa bir seçenekle aynı anlamda olan uzun bir seçenek söz konusu olabilir.)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int result;
	int a_flag, b_flag, c_flag, h_flag, count_flag, line_flag;
	char *b_arg, *count_arg, *line_arg;
	int err_flag;
	int i;

	struct option options[] = {
		{"help", no_argument, NULL, 'h'},
		{"count", required_argument, NULL, 2},
		{"line", optional_argument, NULL, 3},
		{0, 0, 0, 0 },
	};

	opterr = 0;

	a_flag = b_flag = c_flag = h_flag = count_flag = line_flag = 0;
	err_flag = 0;

	while ((result = getopt_long(argc, argv, "ab:ch", options, NULL)) != -1) {
		switch (result) {
		case 'a':
			a_flag = 1;
			break;
		case 'b':
			b_flag = 1;
			b_arg = optarg;
			break;
		case 'c':
			c_flag = 1;
			break;
		case 'h':
			h_flag = 1;
			break;
		case 2:			/* --count */
			count_flag = 1;
			count_arg = optarg;
			break;
		case 3:			/* --line */
			line_flag = 1;
			line_arg = optarg;
			break;
		case '?':
			if (optopt == 'b')
				fprintf(stderr, "-b option must have an argument!..\n");
			else if (optopt == 2)
				fprintf(stderr, "argument must be specified with --count option\n");
			else if (optopt != 0)
				fprintf(stderr, "invalid option: -%c\n", optopt);
			else
				fprintf(stderr, "invalid long option!..\n");

			err_flag = 1;

			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (a_flag)
		printf("-a option used...\n");

	if (b_flag)
		printf("-b option used with argument \"%s\"...\n", b_arg);

	if (c_flag)
		printf("-c option used...\n");

	if (h_flag)
		printf("-h or --help option used...\n");

	if (count_flag)
		printf("--count option specified with \"%s\"...\n", count_arg);

	if (line_flag) {
		if (line_arg != NULL)
			printf("--line option used with optional argument \"%s\"\n", line_arg);
		else
			printf("--line option used without optional argument...\n");
	}

	if (optind != argc) {
		printf("Seçeneksiz (yani normal) argümanlar:\n");
		for (i = optind; i < argc; ++i)
			printf("%s\n", argv[i]);
	}

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev çözümü (HomeWork-01-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE		5

char **split(char *str, const char *delim);

int main(void)
{
	char names[] = "ali  , veli   , selami,   ayşe,    fatma, hüseyin, sacit";
	char **str;
	int i;

	if ((str = split(names, ", ")) == NULL) {
		fprintf(stderr, "cannot split!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; str[i] != NULL; ++i)
		puts(str[i]);

	free(str);

	return 0;
}

char **split(char *str, const char *delim)
{
	char *s;
	char **tokens = NULL, **temp;
	int i;

	for (i = 0, s = strtok(str, delim); s != NULL; s = strtok(NULL, delim), ++i) {
		if (i % CHUNK_SIZE == 0) {
			if ((temp = (char **)realloc(tokens, sizeof(char *) * (i + CHUNK_SIZE + 1))) == NULL) {
				free(tokens);
				return NULL;
			}
		}
		tokens = temp;
		tokens[i] = s;
	}

	tokens[i] = NULL;

	return tokens;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev çözümü (HomeWork-01-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE		5

char **split(char *str, const char *delim);

int main(void)
{
	char names[] = "ali  , veli   , selami,   ayşe,    fatma, hüseyin, sacit";
	char **str;
	int i;

	if ((str = split(names, ", ")) == NULL) {
		fprintf(stderr, "cannot split!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; str[i] != NULL; ++i)
		puts(str[i]);

	free(str);

	return 0;
}

char **split(char *str, const char *delim)
{
	char *s;
	char **tokens = NULL, **temp;
	int i;

	for (i = 0, s = strtok(str, delim); s != NULL; s = strtok(NULL, delim), ++i) {
		if (i % CHUNK_SIZE == 0) {
			if ((temp = (char **)realloc(tokens, sizeof(char *) * (i + CHUNK_SIZE + 1))) == NULL) {
				free(tokens);
				return NULL;
			}
		}
		tokens = temp;
		tokens[i] = s;
	}

	tokens[i] = NULL;

	return tokens;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev çözümü (HomeWork-01-2)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE		5

char **split2(const char *str, const char *delim)
{
	char *s, *news, *newstr;
	char **tokens = NULL, **temp;
	int i;

	if ((newstr = (char *)malloc(strlen(str) + 1)) == NULL)
		return NULL;
	strcpy(newstr, str);

	for (i = 0, s = strtok(newstr, delim); s != NULL; s = strtok(NULL, delim), ++i) {
		if (i % CHUNK_SIZE == 0) {
			if ((temp = (char **)realloc(tokens, sizeof(char *) * (i + CHUNK_SIZE + 1))) == NULL) {
				free(newstr);
				free(tokens);
				return NULL;
			}
		}
		tokens = temp;

		if ((news = (char *)malloc(strlen(s) + 1)) == NULL) {
			free(newstr);
			free(tokens);
			return NULL;
		}
		strcpy(news, s);
		tokens[i] = news;
	}

	tokens[i] = NULL;

	free(newstr);

	return tokens;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev Çözümü (HomwWork-01-3)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_SIZE				10000
#define PARTIAL_COUNT			10
#define PARTIAL_SIZE			(TOTAL_SIZE / PARTIAL_COUNT)
#define RANDOM_FILE_PATH		"random.dat"
#define RESULT_FILE_PATH		"result.dat"


struct merge_info {
	FILE *f;
	int curval;
};

FILE *create_random_file(void);
void bsort(int *pi, size_t size);
int getmin_index(const struct merge_info *mi, int size);
int verify_result(FILE *f, int size);

int main(void)
{
	FILE *fr, *fd;
	struct merge_info mi[PARTIAL_COUNT];
	int i, size, min_index;
	int *buf;


	if ((fr = create_random_file()) == NULL) {
		fprintf(stderr, "cannot create random file!..\n");
		exit(EXIT_FAILURE);
	}

	if ((fd = fopen(RESULT_FILE_PATH, "w+b")) == NULL) {
		fprintf(stderr, "cannot create destination file!..\n");
		exit(EXIT_FAILURE);
	}

	if ((buf = (int *)malloc(PARTIAL_SIZE * sizeof(int))) == NULL) {
		fprintf(stderr, "cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	rewind(fr);
	for (i = 0; i < PARTIAL_COUNT; ++i) {
		if (fread(buf, sizeof(int), PARTIAL_SIZE, fr) != PARTIAL_SIZE) {
			fprintf(stderr, "cannot read random file!...\n");
			exit(EXIT_FAILURE);
		}

		bsort(buf, PARTIAL_SIZE);
		if ((mi[i].f = tmpfile()) == NULL) {
			fprintf(stderr, "cannot create temporary file!..\n");
			free(buf);
			exit(EXIT_FAILURE);
		}

		if (fwrite(buf, sizeof(int), PARTIAL_SIZE, mi[i].f) != PARTIAL_SIZE) {
			fprintf(stderr, "cannot read random file!...\n");
			exit(EXIT_FAILURE);
		}
		rewind(mi[i].f);
	}
	fclose(fr);

	for (i = 0; i < PARTIAL_COUNT; ++i)
		if (fread(&mi[i].curval, sizeof(int), 1, mi[i].f) != 1) {
			fprintf(stderr, "cannot read temporary file!..\n");
			exit(EXIT_FAILURE);
		}
	size = PARTIAL_COUNT;

	while (size > 0) {
		min_index = getmin_index(mi, size);
		if (fwrite(&mi[min_index].curval, sizeof(int), 1, fd) != 1) {
			fprintf(stderr, "cannot write destination file!..\n");
			exit(EXIT_FAILURE);
		}

		if (fread(&mi[min_index].curval, sizeof(int), 1, mi[min_index].f) != 1) {
			if (ferror(mi[min_index].f)) {
				fprintf(stderr, "cannot read temporary file!..\n");
				exit(EXIT_FAILURE);
			}
			mi[min_index] = mi[size - 1];
			--size;
		}
	}

	rewind(fd);
	printf("%s\n", verify_result(fd, TOTAL_SIZE) ? "Verify Ok...\n" : "Verify Failed!..\n");

	free(buf);
	fclose(fd);

	return 0;
}

FILE *create_random_file(void)
{
	FILE *f;
	int i, val;

	srand((unsigned)time(NULL));

	if ((f = fopen(RANDOM_FILE_PATH, "w+b")) == NULL)
		return NULL;

	for (i = 0; i < TOTAL_SIZE; ++i) {
		val = rand();
		if (fwrite(&val, sizeof(int), 1, f) != 1)
			return NULL;
	}

	return f;
}

void bsort(int *pi, size_t size)
{
	size_t i, k;
	int temp;

	for (i = 0; i < size - 1; ++i)
		for (k = 0; k < size - 1 - i; ++k)
			if (pi[k] > pi[k + 1]) {
				temp = pi[k];
				pi[k] = pi[k + 1];
				pi[k + 1] = temp;
			}
}

int getmin_index(const struct merge_info *mi, int size)
{
	int i, min_index = 0;

	for (i = 1; i < size; ++i)
		if (mi[i].curval < mi[min_index].curval)
			min_index = i;

	return min_index;
}

int verify_result(FILE *f, int size)
{
	int val, prev_val;
	int i;

	if (fread(&prev_val, sizeof(int), 1, f) != 1)
		return 0;

	for (i = 1; i < size; ++i) {
		if (fread(&val, sizeof(int), 1, f) != 1)
			return 0;
		if (val < prev_val)
			return 0;
		prev_val = val;
	}

	return ftell(f) == size * sizeof(int);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev Çözümü (HomwWork-02-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* myhead.c */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void write_lines(FILE *f, int nlines);
void write_chars(FILE *f, int nchars);

int main(int argc, char *argv[])
{
	int result;
	int c_flag, n_flag, v_flag, help_flag, version_flag, err_flag;
	const char *c_arg, *n_arg;
	int i, nlines, nchars;
	FILE *f;

	struct option options[] = {
		{"bytes", required_argument, NULL, 'c'},
		{"line", required_argument, NULL, 'n'},
		{"verbose", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 1},
		{"version", no_argument, NULL, 2},
		{ 0, 0, 0, 0}
	};

	opterr = 0;

	c_flag = n_flag = v_flag = help_flag = version_flag = 0;
	err_flag = 0;

	while ((result = getopt_long(argc, argv, "c:n:v", options, NULL)) != -1) {
		switch (result) {
		case 'c':
			c_flag = 1;
			c_arg = optarg;
			break;
		case 'n':
			n_flag = 1;
			n_arg = optarg;
			break;
		case 'v':
			v_flag = 1;
			break;
		case 1:
			help_flag = 1;
			break;
		case 2:
			version_flag = 2;
			break;
		case '?':
			switch (optopt) {
			case 'c':
				fprintf(stderr, "-c or --bytes must have argument!..\n");
				break;
			case 'n':
				fprintf(stderr, "-n or --lines must have argument!..\n");
				break;
			default:
				if (optopt != 0)
					fprintf(stderr, "invalid option: -%c\n", optopt);
				else
					fprintf(stderr, "invalid long option!..\n");
			}
			err_flag = 1;
			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (help_flag) {
		if (c_flag || n_flag || v_flag || version_flag) {
			fprintf(stderr, "--help option must not be used with other options!..\n");
			exit(EXIT_FAILURE);
		}
		printf("Usage: myhead [OPTION]... [FILE]...\n");
		exit(EXIT_SUCCESS);
	}

	if (version_flag) {
		if (c_flag || n_flag || v_flag || help_flag) {
			fprintf(stderr, "--version option must not be used with other options!..\n");
			exit(EXIT_FAILURE);
		}
		printf("1.0\n");
		exit(EXIT_SUCCESS);
	}

	if (n_flag && c_flag) {
		fprintf(stderr, "-n (--line) and -c (--bytes) flags cannot be used together!..\n");
		exit(EXIT_FAILURE);
	}

	if (optind == argc) {
		fprintf(stderr, "at least one file must be specified!..\n");
		exit(EXIT_FAILURE);
	}

	if (argc - optind > 1)
		v_flag = 1;

	if (n_flag)
		nlines = (int)strtol(n_arg, NULL, 10);
	else if (c_flag)
		nchars = (int)strtol(c_arg, NULL, 10);
	else {
		n_flag = 1;
		nlines = 10;
	}

	for (i = optind; i < argc; ++i) {
		if ((f = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "file not found or cannot open: %s\n", argv[i]);
			continue;
		}
		if (v_flag)
			printf("==> %s <==\n", argv[i]);
		if (n_flag)
			write_lines(f, nlines);
		else if (c_flag)
			write_chars(f, nchars);
	}

	return 0;
}

void write_lines(FILE *f, int nlines)
{
	int ch;
	int n = 0;

	while ((ch = fgetc(f)) != EOF && n < nlines) {
		putchar(ch);
		if (ch == '\n')
			++n;
	}

	if (ferror(f))
		fprintf(stderr, "cannot read file!..\n");
}

void write_chars(FILE *f, int nchars)
{
	int ch;
	int i;

	for (i = 0; i < nchars && (ch = fgetc(f)) != EOF; ++i)
		putchar(ch);

	if (ferror(f))
		fprintf(stderr, "cannot read file!..\n");
	putchar('\n');
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Object dump utility

	myod [--top --header -x -o -t -h] <dosya listesi>
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

/* Symbolic Constans */

#define DEF_LINE                10
#define HEX_OCTAL_LINE_LEN      16

/* Function Prorotypes */

int print_text(FILE *f, int nline);
int print_hex_octal(FILE *f, int nline, int hexflag);

int main(int argc, char *argv[])
{
	int result, err_flag = 0;
	int x_flag = 0, o_flag = 0, t_flag = 0, top_flag = 0, header_flag = 0;
	char *top_arg;
	struct option options[] = {
		{"top", optional_argument, NULL, 1},
		{"header", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};
	FILE *f;
	int i, nline = -1;

	opterr = 0;
	while ((result = getopt_long(argc, argv, "xoth", options, NULL)) != -1) {
		switch (result) {
		case 'x':
			x_flag = 1;
			break;
		case 'o':
			o_flag = 1;
			break;
		case 't':
			t_flag = 1;
			break;
		case 'h':
			header_flag = 1;
			break;
		case 1:
			top_flag = 1;
			top_arg = optarg;
			break;
		case '?':
			if (optopt != 0)
				fprintf(stderr, "invalid switch: -%c\n", optopt);
			else
				fprintf(stderr, "invalid switch: %s\n", argv[optind - 1]);  /* argv[optind - 1] dokümante edilmemiş */
			err_flag = 1;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (x_flag + o_flag + t_flag > 1) {
		fprintf(stderr, "only one option must be specified from -o, -t, -x\n");
		exit(EXIT_FAILURE);
	}
	if (x_flag + o_flag + t_flag == 0)
		t_flag = 1;

	if (top_flag)
		nline = top_arg != NULL ? (int)strtol(top_arg, NULL, 10) : DEF_LINE;

	if (optind == argc) {
		fprintf(stderr, "at least one file must be specified!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = optind; i < argc; ++i) {
		if ((f = fopen(argv[i], "rb")) == NULL) {
			fprintf(stderr, "cannot open file: %s\n", argv[i]);
			continue;
		}

		if (header_flag)
			printf("%s\n\n", argv[i]);

		if (t_flag)
			result = print_text(f, nline);
		else if (x_flag)
			result = print_hex_octal(f, nline, 1);
		else
			result = print_hex_octal(f, nline, 0);

		if (i != argc - 1)
			putchar('\n');

		if (!result)
			fprintf(stderr, "cannot read file: %s\n", argv[i]);

		fclose(f);
	}

	return 0;
}

int print_text(FILE *f, int nline)
{
	int ch;
	int count;

	if (nline == -1)
		while ((ch = fgetc(f)) != EOF)
			putchar(ch);
	else {
		count = 0;
		while ((ch = fgetc(f)) != EOF && count < nline) {
			putchar(ch);
			if (ch == '\n')
				++count;
		}
	}

	return !ferror(f);
}

int print_hex_octal(FILE *f, int nline, int hexflag)
{
	int ch, i, count;
	const char *off_str, *ch_str;

	off_str = hexflag ? "%07X " : "%012o";
	ch_str = hexflag ? "%02X%c" : "%03o%c";

	if (nline == -1)
		for (i = 0; (ch = fgetc(f)) != EOF; ++i) {
			if (i % HEX_OCTAL_LINE_LEN == 0)
				printf(off_str, i);
			printf(ch_str, ch, i % HEX_OCTAL_LINE_LEN == HEX_OCTAL_LINE_LEN - 1 ? '\n' : ' ');
		}

	else {
		count = 0;
		for (i = 0; (ch = fgetc(f)) != EOF && count < nline; ++i) {
			if (i % HEX_OCTAL_LINE_LEN == 0)
				printf(off_str, i);
			printf(ch_str, ch, i % HEX_OCTAL_LINE_LEN == HEX_OCTAL_LINE_LEN - 1 ? '\n' : ' ');
			if (ch == '\n')
				++count;
		}
	}

	if (i % HEX_OCTAL_LINE_LEN != 0)
		putchar('\n');

	return !ferror(f);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde bir API fonksiyonu başarısız olmuşsa neden başarısız olduğu GetLastError isimli fonksiyonla tespit edilir. 
	Bu fonksiyonun prototipi şöyledir:

	DWORD GetLastError(void);

	Fonksiyon her farklı error gerekçesi için değişk bir değer vermektedir. Bu değerler aynı zamanda <windows.h> içerisinde
	ERROR_XXXX biçiminde sembolik sabitlerle define edilmiştir. Hatanın nedenini yazı biçiminde oluştuyrmak için FormatMessage isimli
	yardımcı bir API fonksiyonu da vardır. Ancak bu fonksiyonun kullanımı biraz karmaşıktır. Bunun yerine biz ExitSys isimli bir sarma (wrapper)
	fonksiyon yazacağız. Bu fonksiyon önce bizim verdiğimiz yazıyı, sonra ':' karakterini sonra da hata kodunu stderr dosyasına yazdırıp
	programı EXIT_FAILURE exit kodu ile sonlandırmaktadır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	if (CreateSemaphore(NULL, -10, 1, "") == NULL)
		ExitSys("CreateSemaphore");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde bir POSIX fonksiyonu başarısız olduğunda errno değerinin yazısal karşılığı strerror fonksiyonuyla elde edilebilir.

	#include <string.h>

	char *strerror(int err);

	Fonksiyon static bir alanın adresiyle geri dönmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int result;

	if ((result = open("test.dat", O_RDONLY)) == -1) {
		fprintf(stderr, "Open failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("success...\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde perror fonksiyonu (ki aynı zamanda perror bir standart C fonksiyonudur) önce programcının belirlediği mesajı, 
	sonra ':' karakterini sonra da errno değişkeninin değerinin yazısal karşılığını stderr dosyasına yazdırmaktadır.

	#include <stdio.h>

	void perror(const char *msg);

-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int result;

	if ((result = open("test.dat", O_RDONLY)) == -1) {
		perror("open failed");
		exit(EXIT_FAILURE);
	}

	printf("success...\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Genellikle UNIX/Linux sistemlerinde de bir POSIX fonksiyonu başarısız olduğunda programcı hata yazısını ekrana basıp programı sonlandırmaktadır.
	Bu işlem çok yapıldığından dolayı bir sarma fonksiyona (wrapper function) devredilebilir. Biz de kursumuzda exit_sys isimli bir sarma fonksiyon kullanacağız:

	void exit_sys(const char *msg)
	{
		perror(msg);

		exit(EXIT_FAILURE);
	}

-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void exit_sys(const char *msg);

int main(void)
{
	int result;

	if ((result = open("test.dat", O_RDONLY)) == -1)
		exit_sys("open");

	printf("success...\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Handle sistemine bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* Test.c */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void)
{
	HMATRIX hMatrix;

	if ((hMatrix = CreateMatrix(3, 3)) == NULL) {
		fprintf(stderr, "cannot create matrix!..\n");
		exit(EXIT_FAILURE);
	}

	SetElem(hMatrix, 0, 0, 1);
	SetElem(hMatrix, 0, 1, 2);
	SetElem(hMatrix, 0, 2, 3);

	SetElem(hMatrix, 1, 0, 4);
	SetElem(hMatrix, 1, 1, 5);
	SetElem(hMatrix, 1, 2, 6);

	SetElem(hMatrix, 2, 0, 7);
	SetElem(hMatrix, 2, 1, 7);
	SetElem(hMatrix, 2, 2, 9);

	DispMatrix(hMatrix);

	CloseMatrix(hMatrix);

	return 0;
}

/* Matrix.h */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

HMATRIX CreateMatrix(size_t rowSize, size_t colSize)
{
	HMATRIX hMatrix;

	if ((hMatrix = (HMATRIX)malloc(sizeof(MATRIX))) == NULL)
		return NULL;

	if ((hMatrix->pArray = (DATATYPE *)malloc(rowSize * colSize * sizeof(DATATYPE))) == NULL) {
		free(hMatrix);
		return NULL;
	}
	hMatrix->rowSize = rowSize;
	hMatrix->colSize = colSize;

	return hMatrix;
}

void CloseMatrix(HMATRIX hMatrix)
{
	free(hMatrix->pArray);
	free(hMatrix);
}

BOOL SetElem(HMATRIX hMatrix, size_t row, size_t col, int val)
{
	if (row >= hMatrix->rowSize || col >= hMatrix->colSize)
		return FALSE;

	hMatrix->pArray[row * hMatrix->colSize + col] = val;

	return TRUE;
}

int GetElem(HMATRIX hMatrix, size_t row, size_t col)
{
	return hMatrix->pArray[row * hMatrix->colSize + col];
}

void DispMatrix(HMATRIX hMatrix)
{
	size_t i, k;

	for (i = 0; i < hMatrix->rowSize; ++i) {
		for (k = 0; k < hMatrix->colSize; ++k)
			printf("%d ", GetElem(hMatrix, i, k));
		printf("\n");
	}
}

/* Test.c */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void)
{
	HMATRIX hMatrix;

	if ((hMatrix = CreateMatrix(3, 3)) == NULL) {
		fprintf(stderr, "cannot create matrix!..\n");
		exit(EXIT_FAILURE);
	}

	SetElem(hMatrix, 0, 0, 1);
	SetElem(hMatrix, 0, 1, 2);
	SetElem(hMatrix, 0, 2, 3);

	SetElem(hMatrix, 1, 0, 4);
	SetElem(hMatrix, 1, 1, 5);
	SetElem(hMatrix, 1, 2, 6);

	SetElem(hMatrix, 2, 0, 7);
	SetElem(hMatrix, 2, 1, 7);
	SetElem(hMatrix, 2, 2, 9);

	DispMatrix(hMatrix);

	CloseMatrix(hMatrix);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki handle sistemind HMATRIX isimli handle türü void * olarak alınıp handle alanı programcıdan gizlenebilir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* Matrix.h */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stddef.h>

/* Symbolic Constants */

#define TRUE		1
#define FALSE		0

/* Type declarations */

typedef int BOOL;
typedef int DATATYPE;

typedef struct tagMATRIX {
	DATATYPE *pArray;
	size_t rowSize;
	size_t colSize;
} MATRIX;

typedef void *HMATRIX;

/* Function Prototypes */

HMATRIX CreateMatrix(size_t rowSize, size_t colSize);
void CloseMatrix(HMATRIX hMatrix);
BOOL SetElem(HMATRIX hMatrix, size_t row, size_t col, int val);
int GetElem(HMATRIX hMatrix, size_t row, size_t col);
void DispMatrix(HMATRIX hMatrix);

#endif

/* Matrix.h */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

HMATRIX CreateMatrix(size_t rowSize, size_t colSize)
{
	MATRIX *pMatrix;

	if ((pMatrix = (MATRIX *)malloc(sizeof(MATRIX))) == NULL)
		return NULL;

	if ((pMatrix->pArray = (DATATYPE *)malloc(rowSize * colSize * sizeof(DATATYPE))) == NULL) {
		free(pMatrix);
		return NULL;
	}
	pMatrix->rowSize = rowSize;
	pMatrix->colSize = colSize;

	return pMatrix;
}

void CloseMatrix(HMATRIX hMatrix)
{
	MATRIX *pMatrix = (MATRIX *)hMatrix;

	free(pMatrix->pArray);
	free(pMatrix);
}

BOOL SetElem(HMATRIX hMatrix, size_t row, size_t col, int val)
{
	MATRIX *pMatrix = (MATRIX *)hMatrix;

	if (row >= pMatrix->rowSize || col >= pMatrix->colSize)
		return FALSE;

	pMatrix->pArray[row * pMatrix->colSize + col] = val;

	return TRUE;
}

int GetElem(HMATRIX hMatrix, size_t row, size_t col)
{
	MATRIX *pMatrix = (MATRIX *)hMatrix;

	return pMatrix->pArray[row * pMatrix->colSize + col];
}

void DispMatrix(HMATRIX hMatrix)
{
	size_t i, k;
	MATRIX *pMatrix = (MATRIX *)hMatrix;

	for (i = 0; i < pMatrix->rowSize; ++i) {
		for (k = 0; k < pMatrix->colSize; ++k)
			printf("%d ", GetElem(hMatrix, i, k));
		printf("\n");
	}
}

/* Test.c */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void)
{
	HMATRIX hMatrix;

	if ((hMatrix = CreateMatrix(3, 3)) == NULL) {
		fprintf(stderr, "cannot create matrix!..\n");
		exit(EXIT_FAILURE);
	}

	SetElem(hMatrix, 0, 0, 1);
	SetElem(hMatrix, 0, 1, 2);
	SetElem(hMatrix, 0, 2, 3);

	SetElem(hMatrix, 1, 0, 4);
	SetElem(hMatrix, 1, 1, 5);
	SetElem(hMatrix, 1, 2, 6);

	SetElem(hMatrix, 2, 0, 7);
	SetElem(hMatrix, 2, 1, 7);
	SetElem(hMatrix, 2, 2, 9);

	DispMatrix(hMatrix);

	CloseMatrix(hMatrix);

	return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Ödev çözümü (HomeWork-03-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int result;
	int c_flag, l_flag, L_flag, w_flag, help_flag, version_flag;
	int err_flag;
	int i;
	int lc, wc, cc, lcc, max_lcc, max_cc;
	int ch, flag;
	FILE *f;
	const char *delim = " \t\n.,!*-";

	struct option options[] = {
		{"bytes", no_argument, NULL, 'c'},
		{"lines", no_argument, NULL, 'l'},
		{"max_line_length", no_argument, NULL, 'L'},
		{"words", no_argument, NULL, 'w'},
		{"help", no_argument, NULL, 1},
		{"version", no_argument, NULL, 2},
		{0, 0, 0, 0 },
	};

	opterr = 0;

	c_flag = l_flag = L_flag = w_flag = help_flag = 0;
	version_flag = err_flag = 0;

	while ((result = getopt_long(argc, argv, "clLw", options, NULL)) != -1) {
		switch (result) {
		case 'c':
			c_flag = 1;
			break;
		case 'l':
			l_flag = 1;
			break;
		case 'L':
			L_flag = 1;
			break;
		case 'w':
			w_flag = 1;
			break;
		case 1:			            /* --help */
			help_flag = 1;
			break;
		case 2:                     /* --version */
			version_flag = 1;
			break;
		case '?':
			fprintf(stderr, "invalid option!..\n");
			err_flag = 1;

			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (version_flag && (c_flag || l_flag || L_flag || w_flag)) {
		fprintf(stderr, "--version must not be used with other options!..\n");
		exit(EXIT_FAILURE);
	}

	if (help_flag && (c_flag || l_flag || L_flag || w_flag)) {
		fprintf(stderr, "--help must not be used with other options!..\n");
		exit(EXIT_FAILURE);
	}

	if (help_flag) {
		printf("usage: wc [-cwlL][--line, --help, --version] [path list]\n");
		exit(EXIT_SUCCESS);
	}

	if (version_flag) {
		printf("version 1.0\n");
		exit(EXIT_SUCCESS);
	}

	if (optind == argc) {
		fprintf(stderr, "at least one file must be specified!..\n");
		exit(EXIT_FAILURE);
	}

	max_cc = 0;
	for (i = optind; i < argc; ++i) {
		if ((f = fopen(argv[i], "r")) == NULL)
			continue;
		fseek(f, 0, SEEK_END);
		cc = ftell(f);
		if (cc > max_cc)
			max_cc = cc;
		fclose(f);
	}

	max_cc = (int)log10(max_cc) + 1;
	if (max_cc < 3)
		max_cc = 3;

	for (i = optind; i < argc; ++i) {
		if ((f = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "file not found or cannot open: %s\n", argv[i]);
			continue;
		}

		cc = wc = lc = max_lcc = 0;
		flag = 1;
		lcc = 0;
		while ((ch = fgetc(f)) != EOF) {
			++cc;
			if (ch == '\n') {
				++lc;
				if (lcc > max_lcc)
					max_lcc = lcc;
				lcc = 0;
			}
			else
				++lcc;
			if (strchr(delim, ch))
				flag = 1;
			else if (flag) {
				flag = 0;
				++wc;
			}
		}

		if (l_flag + w_flag + c_flag + L_flag == 0)
			printf("%*d %*d %*d ", max_cc, cc, max_cc, wc, max_cc, cc);
		else {
			if (l_flag)
				printf("%*d ", max_cc, lc);
			if (w_flag)
				printf("%*d ", max_cc, wc);
			if (c_flag)
				printf("%*d ", max_cc, cc);
			if (L_flag)
				printf("%*d ", max_cc, max_lcc);
		}
		printf("%s\n", argv[i]);
	}

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde aşağı seviyeli olarak bir dosyayı açmak (ya da yaratmak) için CreateFile API fonksiyonu, 
	kapatmak için CloseHandle isimli API fonksiyonu kullanılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hFile;

	if ((hFile = CreateFile("Mest.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	printf("Ok\n");

	CloseHandle(hFile);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-----------------------------------------------------------------------------------------------------------------------------------------
	ReadFile Fonksiyonu ile bir text dosyanın okunarak ekrana yazdırılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUF_SIZE		4096

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hFile;
	char buf[BUF_SIZE + 1];
	DWORD dwRead;
	BOOL bResult;

	if ((hFile = CreateFile("Test.txt", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	while ((bResult = ReadFile(hFile, buf, BUF_SIZE, &dwRead, NULL)) && dwRead > 0) {
		buf[dwRead] = '\0';
		printf("%s", buf);
	}

	if (!bResult)
		ExitSys("ReadFile");

	CloseHandle(hFile);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta ReadFile ve WriteFile fonksiyonlarının kullanımına bir örnek: Dosya Kopyalama.
	Aslında dosya kopyalamak için daha hızlı çalışabilen CopyFile isimli bir API fonksiyonu da bulunmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUF_SIZE		4096

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char *argv[])
{
	HANDLE hFileSource, hFileDest;
	char buf[BUF_SIZE];
	DWORD dwRead, dwWritten;
	BOOL bResult;

	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((hFileSource = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	if ((hFileDest = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	while ((bResult = ReadFile(hFileSource, buf, BUF_SIZE, &dwRead, NULL)) && dwRead > 0) {
		if (!WriteFile(hFileDest, buf, dwRead, &dwWritten, NULL))
			ExitSys("WriteFile");
		if (dwWritten != dwRead) {
			fprintf(stderr, "Cannot file write, maybe disk full!..\n");
			exit(EXIT_FAILURE);
		}
	}
	if (!bResult)
		ExitSys("WriteFile");

	CloseHandle(hFileSource);
	CloseHandle(hFileDest);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	open POSIX fonksiyonu ile dosya açmaya bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main()
{
	int fd;

	if ((fd = open("test.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		exit_sys("open");

	printf("Ok\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	read POSIX fonksiyonu ile dosyadan okuma yapılmasına örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main()
{
	int fd;
	unsigned char buf[1024];
	ssize_t result;
	ssize_t i;

	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if ((result = read(fd, buf, 1024)) == -1)
		exit_sys("read");

	for (i = 0; i < result; ++i)
		printf("%02X%c", buf[i], i % 16 == 15 ? '\n' : ' ');
	printf("\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde dosya kopyalamaya bir örnek. 

	./mycp [-i -n][--interactive --no-clobber] <source path> <destination path>

	Bir dosyanın olup olmadığını anlamak için ve ilgili prosesin dosyaya okuma/yazma/çalıştırma işlemini yapıp yapaayacağını
	anlayabilmek için access isimli bir POSIX fonksiyonu kullanılmaktadır. Bu fonksiyon open ile dosyayı açmaktan daha etkin bu işlemi
	yapabilmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* mycp.c */
*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

#define BUF_SIZE    8192

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	int result;
	int i_flag, n_flag;
	int err_flag;
	char buf[BUF_SIZE];
	int fds, fdd;
	ssize_t n;

	struct option options[] = {
		{"interactive", no_argument, NULL, 'i'},
		{"no-clobber", required_argument, NULL, 'n'},
		{0, 0, 0, 0 },
	};

	opterr = 0;

	i_flag = n_flag = 0;
	err_flag = 0;

	while ((result = getopt_long(argc, argv, "in", options, NULL)) != -1) {
		switch (result) {
		case 'i':
			i_flag = 1;
			break;
		case 'n':
			n_flag = 1;
			break;
		case '?':
			if (optopt != 0)
				fprintf(stderr, "invalid option: -%c\n", optopt);
			else
				fprintf(stderr, "invalid long option!..\n");

			err_flag = 1;

			break;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (argc - optind != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if (n_flag || i_flag) {
		if (access(argv[optind + 1], F_OK) == 0) {
			if (n_flag) {
				fprintf(stderr, "file already exits! (-n specified)\n");
				exit(EXIT_FAILURE);
			}
			if (i_flag) {
				printf("file already exists! Overwrite? (Y/N):");
				if (tolower(getchar()) != 'y')
					exit(EXIT_FAILURE);
			}
		}
	}

	if ((fds = open(argv[optind], O_RDONLY)) == -1)
		exit_sys("open");

	if ((fdd = open(argv[optind + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		exit_sys("open");

	while ((n = read(fds, buf, BUF_SIZE)) > 0)
		if (write(fdd, buf, n) == -1)
			exit_sys("write");

	if (n == -1)
		exit_sys("read");

	close(fds);
	close(fdd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	GUI Programlar özel bir biçimde organize edilmektedir. Bu konu özet olarak kusumuzda ele alınacaktır. Ancak siyah ekranda (konsol ekranında)
	renki yazı yazdırmak, imleci taşımak gibi işlemler için "ANSI Escape kodlarından faydalanılabilmektedir. UNIX/Linux sistemlerinde ayrıca Curses isimli 
	bir kütüphane bu konuda yetenekli işlemler yapmakta kullanılmaktadır. Windows sistemlerinde curses kütüphanesinin yaptıklarının benzerini yapan
	"Console API" fonksiyonları bulunmaktadır. 

	Aşağıda imleci 10, 10 hücresine taşıyıp oraya kırmızı renkte bir hello yazısı basan örnek görülmektedir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	printf("\x1B[10;10H");
	printf("\033[31;1;4mHello\033[0m");
	getchar();

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde siyah ekrana renkli yazılar yazdırabilmek için ve imleçle ilgili işlemler yapabilmek için console API'leri kulanılmaktadır.
	Aşağıda bu API'lere bir örnek verilmiştir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void)
{
	HANDLE hConsole;
	char text[] = "This is a test";
	COORD coord;
	DWORD dwWritten;
	WORD attrs[] = { FOREGROUND_BLUE, FOREGROUND_RED, FOREGROUND_GREEN };

	if ((hConsole = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	coord.X = 10;
	coord.Y = 10;
	SetConsoleCursorPosition(hConsole, coord);

	WriteConsole(hConsole, text, strlen(text), &dwWritten, NULL);

	coord.X = 10;
	coord.Y = 11;
	SetConsoleCursorPosition(hConsole, coord);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	WriteConsole(hConsole, text, strlen(text), &dwWritten, NULL);

	coord.X = 10;
	coord.Y = 12;

	SetConsoleCursorPosition(hConsole, coord);
	WriteConsole(hConsole, "ali", 3, &dwWritten, NULL);
	WriteConsoleOutputAttribute(hConsole, attrs, 3, coord, &dwWritten);

	coord.X = 10;
	coord.Y = 13;


	getchar();

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde open fonksiyonun üçüncü parameresinde verilen erişim hakları nihai durumu belirtmemektedir. Nihai durum üçüncüğ
	parametrede belirtilen erişim haklarının prosesin umask değeri ile işleme sokulmasıyla belirlenir. umask değerindeki set edilen bayraklar 
	open fonksiyınunda belirtilse bile dikkate alınmayacak hakları belirtir. open dışında bazı diğer yaratıcı POSIX fonksiyonları da umask değerini
	dikkate almaktadır. umask değeri üst prosesten alt prosese aktarılmaktadır. Shell prosesinin default umask değeri 022'dir. (Yani S_IWUSR|S_IWGRP)
	Proses kendi umask değerini umask isimli POSIX fonksiyonuyla değiştirebilemketdri 

		#incude <sys/stat.h>
		
		mode_t umask(mode_t mask);

	Aşağıdaki programda prosesin umask değeri 0 yapılarak maske ortadan kaldırılmıştır. 

	Shell prosesinin umask değeri umask shell komutuyla alınıp değiştirilebilmektedir.

-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main()
{
	int fd;

	/* umask(S_IWUSR|S_IWOTH);		default umask */

	umask(0);

	if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
		exit_sys("open");

	close(fd);

	printf("OK\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta dosya silmek için DeleteFile isimli API fonksiyonu bulunmaktadır. remove standart C fonksiyonu aslında bu fonksiyonu çağırmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	if (!DeleteFile("test.txt"))
		ExitSys("DeleteFile");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------
	Dosya taşımak demek o dosyanın diskteki verileri üzerinde değişiklik yapmadan yalnızca dizin girişlerini taşamak demektir. Yani dosya 
	taşıma işlemi sırasında gerçek anlamda bir kopyalama yapılmamaktadır. Windows'ta dosya taşıak için MoveFile API fonksiyonu kullanılır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	if (!MoveFile("Mample.c", "Tample.c", FALSE))
		ExitSys("CopyFile");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde GetFileSize API fonksiyonu açılmış bir dosyanın uzunluğunu bize verir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hFile;
	DWORD dwSize;

	if ((hFile = CreateFile("Tample.c", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	if ((dwSize = GetFileSize(hFile, NULL)) == INVALID_FILE_SIZE)
		if (GetLastError() != NO_ERROR)
			ExitSys("GetFileSize");

	printf("%lu\n", (unsigned long)dwSize);

	CloseHandle(hFile);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Ödev Çözümü (HomwWork-05-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/
/* ga.h */

#ifndef GA_H_
#define GA_H_

#include <Windows.h>

/* Function Prototypes */

BOOL InitGA(void);
void Pos(int row, int col);
void WriteChar(int row, int col, int ch);
void WriteCharAttr(int row, int col, int ch, int attr);
void WriteStr(int row, int col, LPCSTR szStr);
void WriteStrAttribute(int row, int col, LPCSTR szStr, int attr);
void FillChar(int row, int col, int ch, int n);
void FillCharAttr(int row, int col, int ch, int n, int attr);
void VFillChar(int row, int col, int ch, int n);
void VFillCharAttr(int row, int col, int ch, int n, int attr);
void DrawFrame(int row1, int col1, int row2, int col2);

#endif

/* ga.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define BOX_UL	0x250C
#define BOX_UR	0x2510
#define BOX_LL	0x2514
#define BOX_LR	0x2518
#define BOX_H	0x2500
#define BOX_V	0x2502

static HANDLE hStdOut;

BOOL InitGA(void)
{
	if ((hStdOut = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		return FALSE;

	return TRUE;
}

void Pos(int row, int col)
{
	COORD coord;

	coord.X = col;
	coord.Y = row;

	SetConsoleCursorPosition(hStdOut, coord);
}

void WriteChar(int row, int col, int ch)
{
	COORD coord;
	DWORD dwWritten;
	char och = ch;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputCharacter(hStdOut, &och, 1, coord, &dwWritten);
}

void WriteCharAttr(int row, int col, int ch, int attr)
{
	COORD coord;
	DWORD dwWritten;
	char och = ch;
	WORD wAttr = attr;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputAttribute(hStdOut, &wAttr, 1, coord, &dwWritten);
	WriteConsoleOutputCharacter(hStdOut, &och, 1, coord, &dwWritten);
}

void WriteStr(int row, int col, LPCSTR szStr)
{
	COORD coord;
	DWORD dwWritten;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputCharacter(hStdOut, szStr, strlen(szStr), coord, &dwWritten);
}

void WriteStrAttribute(int row, int col, LPCSTR szStr, int attr)
{
	COORD coord;
	DWORD dwWritten;
	WORD wAttr = attr;
	int i;

	coord.X = col;
	coord.Y = row;

	for (i = 0; szStr[i] != '\0'; ++i) {
		WriteConsoleOutputAttribute(hStdOut, &wAttr, 1, coord, &dwWritten);
		++coord.X;
	}

	coord.X = col;

	WriteConsoleOutputCharacter(hStdOut, szStr, i, coord, &dwWritten);
}

void FillChar(int row, int col, int ch, int n)
{
	int i;

	for (i = 0; i < n; ++i) {
		WriteChar(row, col, ch);
		++col;
	}
}

void FillCharAttr(int row, int col, int ch, int n, int attr)
{
	int i;

	for (i = 0; i < n; ++i) {
		WriteCharAttr(row, col, ch, attr);
		++col;
	}
}

void VFillChar(int row, int col, int ch, int n)
{
	int i;

	for (i = 0; i < n; ++i) {
		WriteChar(row, col, ch);
		++row;
	}
}

void VFillCharAttr(int row, int col, int ch, int n, int attr)
{
	int i;

	for (i = 0; i < n; ++i) {
		WriteCharAttr(row, col, ch, attr);
		++row;
	}
}

void DrawFrame(int row1, int col1, int row2, int col2)
{
	COORD coord;
	DWORD dwWritten;
	wchar_t ch;
	int i;

	coord.X = col1;
	coord.Y = row1;
	ch = BOX_UL;

	WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);

	coord.X = col2;
	coord.Y = row1;
	ch = BOX_UR;

	WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);

	coord.X = col1;
	coord.Y = row2;
	ch = BOX_LL;

	WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);

	coord.X = col2;
	coord.Y = row2;
	ch = BOX_LR;

	WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);

	ch = BOX_H;
	for (i = 0; i < col2 - col1 - 1; ++i) {
		coord.X = col1 + 1 + i;
		coord.Y = row1;
		WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);
		coord.Y = row2;
		WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);
	}

	ch = BOX_V;
	for (i = 0; i < row2 - row1 - 1; ++i) {
		coord.X = col1;
		coord.Y = row1 + 1 + i;
		WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);
		coord.X = col2;
		WriteConsoleOutputCharacterW(hStdOut, &ch, 1, coord, &dwWritten);
	}
}

/* test.c */

#include <stdio.h>
#include <stdlib.h>
#include "ga.h"

int main(void)
{
	InitGA();

	DrawFrame(10, 10, 20, 20);
	DrawFrame(22, 10, 25, 15);

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta bir dizin yaratmak için CreateDirectory isimli API fonksiyonu kullanılır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	if (!CreateDirectory("TestDir", NULL))
		ExitSys("CreateDirectory");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta bir dizin silmek için RemoveDirectory isimli API fonksiyonu kullanılır. Ancak bu fonksiyon dizin'in içi boşsa silmeyi yapabilmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	if (!RemoveDirectory("TestDir", NULL))
		ExitSys("CreateDirectory");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde dosya silmek için remove standart C fonksiyonu kullanılabilir. Ancak asıl dosya silen fonksiyon unlink isimli
	POSIX fonksiyonudur. unlink her zaman dizin girişini siler anck dosyanın katı bağ (hard link) sayacını 1 eksilttikten sonra sayaç 
	0'a düşerse dosyanın gerçek bilgilerini de silmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main()
{
	if (unlink("test.txt") == -1)
		exit_sys("unlink");

	printf("sucess...\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde yaratılmış olan bir dosyanın erişim hakları chmod isimli POSIX fonksiyonuyla değiştirilebilir. Ancak bunun için
	chmod fonksiyonunu çağıran prosesin etkin kullanıcı id'sinin (effective user id) dosyanın kullanıcı id'si ile aynı olması (yani prosesin dosyanın 
	sahibi olması) ya da prosesin etkin kullanıcı id'sinin 0 olması (root olması) gerekmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(void)
{
	if (chmod("test.txt", S_IRUSR | S_IWUSR) == -1)
		exit_sys("chmod");

	printf("success...\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde zaten açılmış bir dosyanın erişim haklarını değiştirmek için fchmod fonksiyonu kullanılmaktadır. Dosyanın hangi modda
	açıldığının bir önemi yoktur.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	int fd;

	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if (fchmod(fd, S_IRUSR | S_IWUSR) == -1)
		exit_sys("fchmod");

	close(fd);

	printf("success...\n");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	chmod komutunun octal erişim haklarıyla yazımına ilişkin bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	unsigned int omode;
	mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	mode_t mode;
	int i;

	if (argc < 3) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if (strlen(argv[1]) > 3) {
		fprintf(stderr, "mode must have maximum 3 octal digits!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; argv[1][i] != '\0'; ++i)
		if (argv[1][i] < '0' || argv[1][i] > '7') {
			fprintf(stderr, "invalid octal digit!..\n");
			exit(EXIT_FAILURE);
		}

	sscanf(argv[1], "%o", &omode);
	mode = 0;

	for (i = 0; i < 9; ++i)
		mode |= (omode >> (8 - i) & 1) ? modes[i] : 0;

	for (i = 2; i < argc; ++i)
		if (chmod(argv[i], mode) == -1)
			fprintf(stderr, "%s: %s\n", argv[i], strerror(errno));

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	mkdir POSIX fonksiyonu dizini yaratmak için rmdir POSIX fonksiyonu ise dizini silmek için kullanılmaktadır. 
	Bu örnekte dizin yaratan bir program verilmiştir. Program -m ya da --mode ile yaratılacak dizinin de erişim haklarını almaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <getopt.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	unsigned int omode;
	mode_t mode;
	int m_flag, err_flag;
	char *m_arg;
	int result, i;

	struct option options[] = {
		{"mode", required_argument, NULL, 'm'},
		{0, 0, 0, 0 },
	};

	opterr = 0;

	m_flag = 0;
	err_flag = 0;

	while ((result = getopt_long(argc, argv, "m:", options, NULL)) != -1) {
		switch (result) {
		case 'm':
			m_flag = 1;
			m_arg = optarg;
			break;
		case '?':
			if (optopt == 'm')
				fprintf(stderr, "-m option must have an argument!..\n");
			else if (optopt != 0)
				fprintf(stderr, "invalid option: -%c\n", optopt);
			else
				fprintf(stderr, "invalid long option!..\n");

			err_flag = 1;
		}
	}

	if (err_flag)
		exit(EXIT_FAILURE);

	if (m_flag) {
		if (strlen(m_arg) > 3) {
			fprintf(stderr, "mode must have maximum 3 octal digits!..\n");
			exit(EXIT_FAILURE);
		}

		for (i = 0; m_arg[i] != '\0'; ++i)
			if (m_arg[i] < '0' || m_arg[i] > '7') {
				fprintf(stderr, "invalid octal digit!..\n");
				exit(EXIT_FAILURE);
			}

		sscanf(m_arg, "%o", &omode);

		mode = 0;
		for (i = 0; i < 9; ++i)
			mode |= (omode >> (8 - i) & 1) ? modes[i] : 0;
	}
	else
		mode = S_IRWXU | S_IRWXG | S_IRWXO;

	umask(0);
	for (i = optind; i < argc; ++i)
		if (mkdir(argv[i], mode) == -1)
			fprintf(stderr, "%s: %s\n", argv[i], strerror(errno));

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlrinde stat fonksiyonun kullanılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>

const char *getls_mode(mode_t mode);

int main(int argc, char *argv[])
{
	struct stat finfo;
	int i;

	if (argc == 1) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; ++i) {
		if (stat(argv[i], &finfo) == -1) {
			fprintf(stderr, "stat: %s\n", strerror(errno));
			continue;
		}

		printf("----------------------------\n");
		printf("%s\n\n", argv[i]);
		printf("Mode: %s\n", getls_mode(finfo.st_mode));
		printf("%-20s%lld\n", "Size", (long long)finfo.st_size);
		printf("%-20s%llu\n", "I-Node", (unsigned long long)finfo.st_ino);
		printf("%-20s%lld\n", "User id", (long long)finfo.st_uid);
		printf("%-20s%lld\n", "Group id", (long long)finfo.st_gid);
		printf("%-20s%s", "Last Update", ctime(&finfo.st_mtime));
		printf("%-20s%s", "Last Read", ctime(&finfo.st_atime));
		printf("%-20s%s", "Last I-Node Update", ctime(&finfo.st_ctime));
	}

	return 0;
}

const char *getls_mode(mode_t mode)
{
	static char tmode[11];
	mode_t modef[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	char *modec = "rwx";
	int i;

	if (S_ISREG(mode))
		tmode[0] = '-';
	else if (S_ISDIR(mode))
		tmode[0] = 'd';
	else if (S_ISCHR(mode))
		tmode[0] = 'c';
	else if (S_ISBLK(mode))
		tmode[0] = 'b';
	else if (S_ISFIFO(mode))
		tmode[0] = 'p';
	else if (S_ISLNK(mode))
		tmode[0] = 'l';
	else if (S_ISSOCK(mode))
		tmode[0] = 's';

	for (i = 0; i < 9; ++i)
		tmode[i + 1] = mode & modef[i] ? modec[i % 3] : '-';
	tmode[i + 1] = '\0';        /* may be omitted */

	return tmode;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Kullanıcının isminden hareketle kullanıcı bilgilerini almak için getpwnam, kullanıcı id'sinden hareketle kullanıcı bilgilerini almak için
	getpwuid POSIX fonksiyonları kullanılmaktadır. Bnezer biçimde grup isminden hareketle grup bilgileri almak için getgrnam, grup id'sinden hareketle
	grup bilgilerini almak için ise getgrgid fonksiyonu kullanılmaktadır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

const char *getls_mode(mode_t mode);

int main(int argc, char *argv[])
{
	struct stat finfo;
	int i;
	struct passwd *pwd;
	struct group *grp;

	if (argc == 1) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; ++i) {
		if (stat(argv[i], &finfo) == -1) {
			fprintf(stderr, "stat: %s\n", strerror(errno));
			continue;
		}

		pwd = getpwuid(finfo.st_uid);
		grp = getgrgid(finfo.st_gid);

		printf("----------------------------\n");
		printf("%s\n\n", argv[i]);
		printf("Mode: %s\n", getls_mode(finfo.st_mode));
		printf("%-20s%lld\n", "Size", (long long)finfo.st_size);
		printf("%-20s%llu\n", "I-Node", (unsigned long long)finfo.st_ino);
		printf("%-20s%s(%lld)\n", "User id", pwd ? pwd->pw_name : "?????", (long long)finfo.st_uid);
		printf("%-20s%s(%lld)\n", "Group id", grp ? grp->gr_name : "?????", (long long)finfo.st_gid);
		printf("%-20s%s", "Last Update", ctime(&finfo.st_mtime));
		printf("%-20s%s", "Last Read", ctime(&finfo.st_atime));
		printf("%-20s%s", "Last I-Node Update", ctime(&finfo.st_ctime));
	}

	return 0;
}

const char *getls_mode(mode_t mode)
{
	static char tmode[11];
	mode_t modef[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	char *modec = "rwx";
	int i;

	if (S_ISREG(mode))
		tmode[0] = '-';
	else if (S_ISDIR(mode))
		tmode[0] = 'd';
	else if (S_ISCHR(mode))
		tmode[0] = 'c';
	else if (S_ISBLK(mode))
		tmode[0] = 'b';
	else if (S_ISFIFO(mode))
		tmode[0] = 'p';
	else if (S_ISLNK(mode))
		tmode[0] = 'l';
	else if (S_ISSOCK(mode))
		tmode[0] = 's';

	for (i = 0; i < 9; ++i)
		tmode[i + 1] = mode & modef[i] ? modec[i % 3] : '-';
	tmode[i + 1] = '\0';        /* may be omitted */

	return tmode;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Aşağıdaki programda sistemdeki tüm kullanıcıların ve grupların isimleri yazdırılmıştır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(void)
{
	struct passwd *pwd;
	struct group *grp;

	while ((pwd = getpwent()) != NULL)
		printf("%s\n", pwd->pw_name);

	endpwent();

	printf("------------\n");

	while ((grp = getgrent()) != NULL)
		printf("%s\n", grp->gr_name);

	endgrent();

	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------
	Belli dosyaların ls -l formatıyla yazdırılması örneği
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void exit_sys(const char *msg);
const char *get_ls(const char *path);

int main(int argc, char *argv[])
{
	struct stat finfo;
	int i;

	if (argc == 1) {
		fprintf(stderr, "too few parameters!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; ++i) {
		if (stat(argv[i], &finfo) == -1) {
			fprintf(stderr, "%s: %s\n", strerror(errno), argv[i]);
			continue;
		}
		printf("%s\n", get_ls(argv[i]));
	}

	return 0;
}

const char *get_ls(const char *path)
{
	struct stat finfo;
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd *pass;
	struct group *gr;
	int index = 0;
	int i;

	if (stat(path, &finfo) == -1)
		return NULL;

	if (S_ISREG(finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %llu", (unsigned long long)finfo.st_nlink);

	if ((pass = getpwuid(finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %s", pass->pw_name);

	if ((gr = getgrgid(finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %s", gr->gr_name);

	index += sprintf(buf + index, " %lld", (long long)finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&finfo.st_mtime));

	sprintf(buf + index, " %s", path);

	return buf;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}


/*-------------------------------------------------------------------------------------------------------------------------------------------
	Ödev çözümü (HomeWork-07-1)
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* passgrp.h */

#ifndef PASSGRP_H_
#define PASSGRP_H_

struct passwd {
	char   *pw_name;       /* username */
	char   *pw_passwd;     /* user password */
	uid_t   pw_uid;        /* user ID */
	gid_t   pw_gid;        /* group ID */
	char   *pw_gecos;      /* user information */
	char   *pw_dir;        /* home directory */
	char   *pw_shell;      /* shell program */
};

struct passwd *csd_getpwnam(const char *name);
struct passwd *csd_getpwuid(uid_t uid);
void csd_endpwent(void);
struct passwd *csd_getpwent(void);
void csd_setpwent(void);

#endif

/* passgrp.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "passgrp.h"

#define MAX_LINE_CHAR       4096

static int is_all_ws(const char *str);

static FILE *g_f;

struct passwd *csd_getpwent(void)
{
	static struct passwd pass;
	static char buf[MAX_LINE_CHAR];
	char *str;
	int i;

	if (g_f == NULL)
		if ((g_f = fopen("/etc/passwd", "r")) == NULL)
			return NULL;

	do
		if (fgets(buf, MAX_LINE_CHAR, g_f) == NULL)
			return NULL;
	while (is_all_ws(buf));

	for (str = strtok(buf, ":"), i = 0; str != NULL; str = strtok(NULL, ":"), ++i)
		switch (i) {
		case 0:
			pass.pw_name = str;
			break;
		case 1:
			pass.pw_passwd = str;
			break;
		case 2:
			pass.pw_uid = (uid_t)strtol(str, NULL, 10);
			break;
		case 3:
			pass.pw_gid = (gid_t)strtol(str, NULL, 10);
			break;
		case 4:
			pass.pw_gecos = str;
			break;
		case 5:
			pass.pw_dir = str;
			break;
		case 6:
			pass.pw_shell = str;
			break;
		}

	return &pass;
}

void csd_setpwent(void)
{
	fseek(g_f, 0, SEEK_SET);
}

void csd_endpwent(void)
{
	if (g_f != NULL)
		fclose(g_f);

	g_f = NULL;
}

struct passwd *csd_getpwnam(const char *name)
{
	struct passwd *pass;

	while ((pass = csd_getpwent()) != NULL)
		if (!strcmp(name, pass->pw_name)) {
			csd_endpwent();
			return pass;
		}

	csd_endpwent();

	return NULL;
}

struct passwd *csd_getpwuid(uid_t uid)
{
	struct passwd *pass;

	csd_endpwent();

	while ((pass = csd_getpwent()) != NULL)
		if (uid == pass->pw_uid)
			return pass;

	return NULL;
}

static int is_all_ws(const char *str)
{
	while (*str != '\0') {
		if (!isspace(*str))
			return 0;
		++str;
	}

	return 1;
}

#if 1

int main(void)
{
	struct passwd *pass;

	while ((pass = csd_getpwent()) != NULL) {
		printf("User name: %s\n", pass->pw_name);
		printf("User Id: %lld\n", (long long)pass->pw_uid);
		printf("------------------------\n");
	}

	csd_setpwent();

	while ((pass = csd_getpwent()) != NULL) {
		printf("User name: %s\n", pass->pw_name);
		printf("User Id: %lld\n", (long long)pass->pw_uid);
		printf("------------------------\n");
	}

	csd_endpwent();

	printf("csd_getpwnam test...\n");
	if ((pass = csd_getpwnam("student")) != NULL) {
		printf("User name: %s\n", pass->pw_name);
		printf("User Id: %lld\n", (long long)pass->pw_uid);
	}

	return 0;
}

#endif

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta Dizin içerisindeki dosyaların el edilmesi örneği 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

typedef unsigned my_t;

int main(void)
{
	WIN32_FIND_DATA finfo;
	HANDLE hFindFile;
	SYSTEMTIME st;

	if ((hFindFile = FindFirstFile("c:\\windows\\*.exe", &finfo)) == INVALID_HANDLE_VALUE)
		ExitSys("FindFirstFile");

	do {
		printf("%s\n", finfo.cFileName);
		printf("%d\n", finfo.nFileSizeLow);
		FileTimeToLocalFileTime(&finfo.ftLastWriteTime, &finfo.ftLastWriteTime);
		FileTimeToSystemTime(&finfo.ftLastWriteTime, &st);
		printf("Last Write Time: %02d/%02d/%04d %02d:%02d:%02d\n",
			st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		printf("----------------------------------\n");
	} while (FindNextFile(hFindFile, &finfo));

	FindClose(hFindFile);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}


/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta Dizin içerisindeki dosyaların el edilmesi örneği
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

typedef unsigned my_t;

int main(void)
{
	WIN32_FIND_DATA finfo;
	HANDLE hFindFile;
	SYSTEMTIME st;

	if ((hFindFile = FindFirstFile("c:\\windows\\*.*", &finfo)) == INVALID_HANDLE_VALUE)
		ExitSys("FindFirstFile");

	do {
		printf("%s %s\n", finfo.cFileName, finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : "");
		if (!(finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			printf("%d\n", finfo.nFileSizeLow);
		FileTimeToLocalFileTime(&finfo.ftLastWriteTime, &finfo.ftLastWriteTime);
		FileTimeToSystemTime(&finfo.ftLastWriteTime, &st);
		printf("Last Write Time: %02d/%02d/%04d %02d:%02d:%02d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		printf("----------------------------------\n");
	} while (FindNextFile(hFindFile, &finfo));

	FindClose(hFindFile);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde dizin içerisindeki dosyaların elde edilmesne örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	while (errno = 0, (dent = readdir(dir)) != NULL)
		printf("%s\n", dent->d_name);

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde dizin listesi elde edilirken yalnızca o dizindeki dosyaların isimleri inode numaraları elde edilmektedir. Eğer dosya
	bilgileri elde edilecekse ayrıca stat ya da lstat fonksiyonu uygulanmalıdır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH      4096

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;
	struct stat finfo;
	char path[MAX_PATH];

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		printf("-------------------------------\n");
		printf("%-25s%s\n", dent->d_name, S_ISDIR(finfo.st_mode) ? "<DIR>" : "");
		printf("%lld\n", (long long)finfo.st_size);
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir dizin'in içeriğini ls -l formatıyla yazdıran program. Burada hizalanma uygulanmamıştır
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define MAX_PATH      4096

void exit_sys(const char *msg);
const char *get_ls(const char *path);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;
	struct stat finfo;
	char path[MAX_PATH];

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		printf("%s\n", get_ls(path));
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	return 0;
}

const char *get_ls(const char *path)
{
	struct stat finfo;
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd *pass;
	struct group *gr;
	char *str;
	int index = 0;
	int i;

	if (stat(path, &finfo) == -1)
		return NULL;

	if (S_ISREG(finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %llu", (unsigned long long)finfo.st_nlink);

	if ((pass = getpwuid(finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %s", pass->pw_name);

	if ((gr = getgrgid(finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %s", gr->gr_name);

	index += sprintf(buf + index, " %lld", (long long)finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&finfo.st_mtime));

	str = strrchr(path, '/');
	sprintf(buf + index, " %s", str ? str + 1 : path);

	return buf;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Dizin içeriğini hizalayarak ls -l formatında yazdıran örnek program
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define MAX_PATH      4096

void exit_sys(const char *msg);
const char *get_ls(const char *path, int hlink_digit, int uname_digit, int gname_digit, int size_digit);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;
	struct stat finfo;
	char path[MAX_PATH];
	struct passwd *pass;
	struct group *gr;
	int len;
	int hlink_digit, uname_digit, gname_digit, size_digit;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	hlink_digit = uname_digit = gname_digit = size_digit = 0;

	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		len = (int)log10(finfo.st_nlink) + 1;
		if (len > hlink_digit)
			hlink_digit = len;

		if ((pass = getpwuid(finfo.st_uid)) == NULL)
			exit_sys("getppuid");

		len = (int)strlen(pass->pw_name);
		if (len > uname_digit)
			uname_digit = len;

		if ((gr = getgrgid(finfo.st_gid)) == NULL)
			exit_sys("getgrgid");

		len = (int)strlen(gr->gr_name);
		if (len > gname_digit)
			gname_digit = len;

		len = (int)log10(finfo.st_size) + 1;
		if (len > size_digit)
			size_digit = len;
	}

	if (errno != 0)
		exit_sys("readdir");

	rewinddir(dir);
	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		printf("%s\n", get_ls(path, hlink_digit, uname_digit, gname_digit, size_digit));
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	return 0;
}

const char *get_ls(const char *path, int hlink_digit, int uname_digit, int gname_digit, int size_digit)
{
	struct stat finfo;
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd *pass;
	struct group *gr;
	char *str;
	int index = 0;
	int i;

	if (stat(path, &finfo) == -1)
		return NULL;

	if (S_ISREG(finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %*llu", hlink_digit, (unsigned long long)finfo.st_nlink);

	if ((pass = getpwuid(finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", uname_digit, pass->pw_name);

	if ((gr = getgrgid(finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", gname_digit, gr->gr_name);

	index += sprintf(buf + index, " %*lld", size_digit, (long long)finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&finfo.st_mtime));

	str = strrchr(path, '/');
	sprintf(buf + index, " %s", str ? str + 1 : path);

	return buf;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon göstericileri
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

int main(void)
{
	void (*pf)(void);
	pf = foo;

	pf();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon göstericileri
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int mul(int a, int b)
{
	return a * b;
}

int sub(int a, int b)
{
	return a - b;
}

int main(void)
{
	int (*pf)(int, int);
	int result;

	pf = add;

	result = pf(10, 20);
	printf("%d\n", result);

	pf = mul;

	result = pf(10, 20);
	printf("%d\n", result);

	pf = sub;

	result = pf(10, 20);
	printf("%d\n", result);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon göstericileri
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int *foo(int *a)
{
	return a;
}

int main(void)
{
	int *(*pf)(int *) = foo;
	int a = 10;
	int *pi;


	pi = pf(&a);
	printf("%d\n", a);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon gösterici dizileri
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

int main(void)
{
	void (*a[3])(void);
	int i;

	a[0] = foo;
	a[1] = bar;
	a[2] = tar;

	for (i = 0; i < 3; ++i)
		a[i]();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon gösterici dizilerine ilkdeğer verilmesi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

int main(void)
{
	void (*a[3])(void) = { foo, bar, tar };
	int i;

	for (i = 0; i < 3; ++i)
		a[i]();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon göstericilerine typedef işlemi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

typedef void (*PF)(void);

int main(void)
{
	PF pf;      /* void (*p)(void) pf; */

	pf = foo;
	pf();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir fonksiyonun parametre değişkeni bir fonlsiyon göstericisi olabilir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int a, int (*pf)(int))
{
	int result;

	result = pf(a);

	printf("%d\n", result);
}

int bar(int a)
{
	return a * a;
}

int main(void)
{
	foo(10, bar);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Her ne kadar fonksiyon isimleri zaten fonksiyonların adreslerini belirtiyorsa da yine de istenirse fonksiyon isimleri & operatörüyle kullanılanilir. 
	Yani aslında C'de foo bir fonksiyon belirtmek üzere foo ifadesi ile &foo ifadesi eşdeğerdir. Benzer biçimde foo bir fonksiyon adresi belirtmek üzere
	bu fonksiyonu çağırmak için foo() ifadesiyle tamamen eşdeğer (*foo)() ifadesi de kullanılabilmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

int main(void)
{
	void (*pf)(void);

	pf = &foo;      /* eşdeğeri: pf = foo */

	(*pf)();        /* eşdeğer: pf() */

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon göstericileri callback mekaznizmasının oluşturulması için sıkça kullanılmaktadır. Callback fonksiyon belli bir olay gerçekleştiğinde
	çağrılacak fonksiyona denilmektedir. Yani biz bir fonksiyona bir fonksiyon veririz. O fonksiyon da belli durumlarda bizim verdiğimiz fonksiyonu
	çağırır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foreach(const int *pi, size_t size, void (*pf)(int))
{
	size_t i;

	for (i = 0; i < size; ++i)
		pf(pi[i]);
}

void foo(int a)
{
	printf("%d\n", a * a);
}

int main(void)
{
	int a[] = { 10, 20, 30, 40, 50 };

	foreach(a, 5, foo);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Callback mekanizması fonksiyonları genelleştirmek için kullanılmaktadır. Aşağıdaki ListDir fonksiyonu bizden aldığı dizin ifadesindeki 
	dosyaları tek tek bulur, bizim belirlediğimiz fonksiyonu çağırır. Sonra da bizim fonksiyonumuz geri dönüş değeri pozitifse dizini dolaşmayı durdurur. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <Windows.h>

int ListDir(LPCSTR szPath, BOOL(*pf)(const WIN32_FIND_DATA *))
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	int result;

	if ((hFF = FindFirstFile(szPath, &wfd)) == INVALID_HANDLE_VALUE)
		return -1;

	do {
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (result = pf(&wfd)) > 0)
			return result;
	} while (FindNextFile(hFF, &wfd));

	return 0;
}

int DispFile(const WIN32_FIND_DATA *pff)
{
	printf("%s\n", pff->cFileName);

	return 0;
}

int FindFile(const WIN32_FIND_DATA *pff)
{
	if (!strcmpi(pff->cFileName, "notepad.exe"))
		return 1;

	return 0;
}

BOOL Filter(const WIN32_FIND_DATA *pff)
{
	long long size = (long long)pff->nFileSizeHigh << 32 | pff->nFileSizeLow;

	if (size < 1000)
		printf("%s, %lld\n", pff->cFileName, size);

	return TRUE;
}

int main(void)
{
	int result;

	ListDir("c:\\windows\\*.*", DispFile);
	printf("-----------------------------\n");
	ListDir("c:\\windows\\*.*", Filter);
	printf("-----------------------------\n");

	if ((result = ListDir("c:\\windows\\*.*", FindFile)) == -1) {
		fprintf(stderr, "Path cannot find!..\n");
		exit(EXIT_FAILURE);
	}

	if (result > 0)
		printf("Found!..\n");
	else
		printf("Not Found...\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Her türlü diziyi sıraya dizebilen genel bir sort fonksiyonun callback mekanizmasıyla yazılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void bsort(void *pv, size_t count, size_t width, int (*compare)(const void *, const void *))
{
	size_t i, k, j;
	char *pc = (char *)pv;
	char *pc1, *pc2;
	char temp;

	for (i = 0; i < count - 1; ++i)
		for (k = 0; k < count - 1 - i; ++k) {
			pc1 = pc + k * width;
			pc2 = pc + (k + 1) * width;
			if (compare(pc1, pc2) > 0) {
				for (j = 0; j < width; ++j) {
					temp = pc1[j];
					pc1[j] = pc2[j];
					pc2[j] = temp;
				}
			}
		}
}

struct PERSON {
	char name[32];
	int no;
};

int cmp(const void *pv1, const void *pv2)
{
	const struct PERSON *per1 = (const struct PERSON *)pv1;
	const struct PERSON *per2 = (const struct PERSON *)pv2;

	if (per1->no > per2->no)
		return 1;
	if (per1->no < per2->no)
		return -1;

	return 0;
}

int main(void)
{
	struct PERSON persons[] = {
		{"Ali Serce", 123},
		{"Veli Boz", 782},
		{"Sacit Apaydin", 824},
		{"Macit Flordun", 623},
		{ "Tansu Ciller", 482}
	};

	int i;

	bsort(persons, 5, sizeof(struct PERSON), cmp);

	for (i = 0; i < 5; ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Aslında yukarıda yazdığımız bsort fonksiyonu ile aynı parametrik yapıya sahip qsort isimli bir standart C fonksiyonu da vardır. 

	void qsort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

	Fonksiyonun yine birinci parameresi dizinin başlangıç adresini, ikinci parametresi onun eleman sayısını, üçüncü parametresi bir elemanının 
	byte uzunluğunu, dördüncü parametresi ise karşılaştımra fonksiyonunu belirtmektedir. Bu karşılaştırma fonksiyonu programcı tarafından 
	eğer soldaki eleman sağdaki elemandan büyükse pozitid herhangi bir değere, eğer sağdaki eleman soldaki elemandan büyükse nehgatif herhangi bir değere
	ve iki eleman biribine eşitse 0 değerine geri dönmelidir. C standartlarında fonksiyonun hangi algoritmayı kullanması gerektiği belirtilmemiş olsa da
	tipik olarak fonksiyon derleyicilerde "quick sort" algoritmasını kullanarak gerçekleştirilmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PERSON {
	char name[32];
	int no;
};

int cmp_no(const void *pv1, const void *pv2)
{
	const struct PERSON *per1 = (const struct PERSON *)pv1;
	const struct PERSON *per2 = (const struct PERSON *)pv2;

	if (per1->no > per2->no)
		return 1;
	if (per1->no < per2->no)
		return -1;

	return 0;
}

#include <ctype.h>

int istrcmp(const char *s1, const char *s2)
{
	while (tolower(*s1) == tolower(*s2)) {
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
	}

	return tolower(*s1) - tolower(*s2);
}

int cmp_name(const void *pv1, const void *pv2)
{
	const struct PERSON *per1 = (const struct PERSON *)pv1;
	const struct PERSON *per2 = (const struct PERSON *)pv2;

	return istrcmp(per1->name, per2->name);
}

int main(void)
{
	struct PERSON persons[] = {
		{"ali serce", 123},
		{"Veli Boz", 782},
		{"ali serce ", 824},
		{"macit flordun", 623},
		{"Tansu Ciller", 482},
		{"ali serce", 516}
	};

#define SIZE(persons) (sizeof(persons) / sizeof(*persons))

	int i;

	qsort(persons, , sizeof(struct PERSON), cmp_no);

	for (i = 0; i < SIZE(persons); ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	printf("--------------------------------------\n");

	qsort(persons, SIZE(persons), sizeof(struct PERSON), cmp_name);

	for (i = 0; i < SIZE(persons); ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir gösterici dizisini qsort fonksiyonuyla sıraya dizerken aslında göstericilerin adresleriyle karşılaştırma fonksiyonu çağrılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *pv1, const void *pv2)
{
	const char **ppc1 = (const char **)pv1;
	const char **ppc2 = (const char **)pv2;

	return strcmp(*ppc1, *ppc2);
}

int main(void)
{
	char *names[] = { "ali", "veli", "selami", "ayse", "fatma", "kazim" };
	int i;

	qsort(names, 6, sizeof(char *), compare);

	for (i = 0; i < 6; ++i)
		printf("%s ", names[i]);
	printf("\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde ls -l işleminden elde edilen dosyaların isme göre sıraya dizilerek yazdırılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define MAX_PATH        4096
#define BLOCK_SIZE      32

struct lsinfo {
	struct stat finfo;
	char *name;
};

void exit_sys(const char *msg);
const char *get_ls(const struct lsinfo *lsinfo, int hlink_digit, int uname_digit, int gname_digit, int size_digit);
int cmp_name(const void *lsinfo1, const void *lsinfo2);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;
	struct lsinfo *lsinfo;
	int count;
	char path[MAX_PATH];
	struct passwd *pass;
	struct group *gr;
	int len;
	int hlink_digit, uname_digit, gname_digit, size_digit;
	int i;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	lsinfo = NULL;
	for (count = 0, errno = 0; (dent = readdir(dir)) != NULL; ++count) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (count % BLOCK_SIZE == 0)
			if ((lsinfo = realloc(lsinfo, (count + BLOCK_SIZE) * sizeof(struct lsinfo))) == NULL) {
				fprintf(stderr, "cannot allocate memory!..\n");
				exit(EXIT_FAILURE);
			}
		if ((lsinfo[count].name = (char *)malloc(strlen(dent->d_name) + 1)) == NULL) {
			fprintf(stderr, "cannot allocate memory!...\n");
			exit(EXIT_FAILURE);
		}
		strcpy(lsinfo[count].name, dent->d_name);
		if (stat(path, &lsinfo[count].finfo) == -1)
			exit_sys("stat");
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	hlink_digit = uname_digit = gname_digit = size_digit = 0;

	for (i = 0; i < count; ++i) {
		len = (int)log10(lsinfo[i].finfo.st_nlink) + 1;
		if (len > hlink_digit)
			hlink_digit = len;

		if ((pass = getpwuid(lsinfo[i].finfo.st_uid)) == NULL)
			exit_sys("getppuid");

		len = (int)strlen(pass->pw_name);
		if (len > uname_digit)
			uname_digit = len;

		if ((gr = getgrgid(lsinfo[i].finfo.st_gid)) == NULL)
			exit_sys("getgrgid");

		len = (int)strlen(gr->gr_name);
		if (len > gname_digit)
			gname_digit = len;

		len = (int)log10(lsinfo[i].finfo.st_size) + 1;
		if (len > size_digit)
			size_digit = len;
	}

	qsort(lsinfo, count, sizeof(struct lsinfo), cmp_name);

	for (i = 0; i < count; ++i)
		printf("%s\n", get_ls(&lsinfo[i], hlink_digit, uname_digit, gname_digit, size_digit));

	for (i = 0; i < count; ++i)
		free(lsinfo[i].name);

	free(lsinfo);

	return 0;
}

const char *get_ls(const struct lsinfo *lsinfo, int hlink_digit, int uname_digit, int gname_digit, int size_digit)
{
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd *pass;
	struct group *gr;
	int index = 0;
	int i;

	if (S_ISREG(lsinfo->finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(lsinfo->finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(lsinfo->finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(lsinfo->finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(lsinfo->finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(lsinfo->finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(lsinfo->finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (lsinfo->finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %*llu", hlink_digit, (unsigned long long)lsinfo->finfo.st_nlink);

	if ((pass = getpwuid(lsinfo->finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", uname_digit, pass->pw_name);

	if ((gr = getgrgid(lsinfo->finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", gname_digit, gr->gr_name);

	index += sprintf(buf + index, " %*lld", size_digit, (long long)lsinfo->finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&lsinfo->finfo.st_mtime));

	sprintf(buf + index, " %s", lsinfo->name);

	return buf;
}

int istrcmp(const char *s1, const char *s2)
{
	while (tolower(*s1) == tolower(*s2)) {
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
	}

	return tolower(*s1) - tolower(*s2);
}

int cmp_name(const void *pv1, const void *pv2)
{
	const struct lsinfo *lsinfo1 = (const struct lsinfo *)pv1;
	const struct lsinfo *lsinfo2 = (const struct lsinfo *)pv2;

	return istrcmp(lsinfo1->name, lsinfo2->name);
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	scandir POSIX fonksiyonun kullanıma bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>

void exit_sys(const char *msg);

int mycallback(const struct dirent *de)
{
	if (tolower(de->d_name[0]) == 'a')
		return 1;

	return 0;
}

int main(void)
{
	struct dirent **dents;
	int i, count;

	if ((count = scandir("/usr/include", &dents, mycallback, NULL)) == -1)
		exit_sys("scandir");

	for (i = 0; i < count; ++i)
		printf("%s\n", dents[i]->d_name);

	for (i = 0; i < count; ++i)
		free(dents[i]);

	free(dents);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	scandir POSIX fonksiyonunun kullanımına bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int mycallback(const struct dirent *de)
{
	struct stat finfo;
	char path[4096];

	sprintf(path, "/usr/include/%s", de->d_name);

	if (stat(path, &finfo) == -1)
		exit_sys("stat");

	return finfo.st_size < 1000;
}

int main(void)
{
	struct dirent **dents;
	int i, count;

	if ((count = scandir("/usr/include", &dents, mycallback, NULL)) == -1)
		exit_sys("scandir");

	for (i = 0; i < count; ++i)
		printf("%s\n", dents[i]->d_name);

	for (i = 0; i < count; ++i)
		free(dents[i]);

	free(dents);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon gösterici dizilerine örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

void car(void)
{
	printf("car\n");
}

int main(void)
{
	void (*pfs[4])(void);
	int i;

	pfs[0] = foo;
	pfs[1] = bar;
	pfs[2] = tar;
	pfs[3] = car;

	for (i = 0; i < 4; ++i)
		pfs[i]();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon gösterici dizilerine küme parantezleri kullanılarak ilkdeğerler de verilebilir:
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

void car(void)
{
	printf("car\n");
}

int main(void)
{
	void (*pfs[])(void) = { foo, bar, tar, car };
	int i;

	for (i = 0; i < 4; ++i)
		pfs[i]();

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Komut satırı (REPL) oluşturan bir örnek. Bu örnekte komut bulunduğunda beelirlenen bir fonksiyon çağrılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#define PROMPT					"CSD>"
#define MAX_CMD_LINE			4096
#define MAX_CMD_PARAMS			64

struct CMD {
	char *cmd_text;
	void (*proc)(void);
};

void parse_cmd_line(void);
void proc_dir(void);
void proc_copy(void);
void proc_cls(void);
void proc_rename(void);

char g_cmd_line[MAX_CMD_LINE];
struct CMD g_cmds[] = {
	{"dir", proc_dir},
	{"copy", proc_copy},
	{"cls", proc_cls},
	{"rename", proc_rename},
	{NULL, NULL},
};
char *g_params[MAX_CMD_PARAMS];
int g_nparams;

int main(void)
{
	char *str;
	int i;

	for (;;) {
		printf(PROMPT);
		fgets(g_cmd_line, MAX_CMD_LINE, stdin);
		if ((str = strchr(g_cmd_line, '\n')) != NULL)
			*str = '\0';

		parse_cmd_line();
		if (g_nparams == 0)
			continue;
		if (!strcmp(g_params[0], "exit"))
			break;
		for (i = 0; g_cmds[i].cmd_text != NULL; ++i)
			if (!strcmp(g_cmds[i].cmd_text, g_params[0])) {
				g_cmds[i].proc();
				break;
			}
		if (g_cmds[i].cmd_text == NULL)
			printf("command not found: %s\n\n", g_params[0]);
	}

	return 0;
}

void parse_cmd_line(void)
{
	char *str;

	g_nparams = 0;
	for (str = strtok(g_cmd_line, " \t"); str != NULL; str = strtok(NULL, " \t"))
		g_params[g_nparams++] = str;
	g_params[g_nparams] = NULL;
}

void proc_dir(void)
{
	printf("dir command\n");
}

void proc_copy(void)
{
	if (g_nparams != 3) {
		printf("argument too few or too many!..\n\n");
		return;
	}
}

void proc_cls(void)
{
	if (g_nparams != 1) {
		printf("too many arguments!\n\n");
		return;
	}
	printf("cls command\n");
}

void proc_rename(void)
{
	printf("rename command\n");
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir fonksiyonun adresini farklı türden bir fonksiyon gösterisine atarken tür dönüştürmesi yapmak gerekir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int a)
{
	printf("foo: %d\n", a);
}

int main(void)
{
	void (*pf)(void);
	void (*pf_original)(int);

	pf = (void (*)(void))foo;

	/* ..... */

	pf_original = (void (*) (int))pf;
	pf_original(100);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	C'de fonksiyon adresleri void bir göstericiye atanamaz. Tür dönüştürme operatörüyle fonksiyon adresleri data adreslerine (örneğin void * türüne)
	dönüştürülemez. Bunun tersi de yapılamaz. Ancak hile yoluyla bir fonksiyon adresi bir data adresine aşağıdaki gibi atanabilmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int a)
{
	printf("foo: %d\n", a);
}

int main(void)
{
	void *pv;
	void (*pf)(int) = foo;		/* geçerli */

	pv = *(void **)&pf;			/* kandırmaca yol, ama standart bakımından geçerli */
	/* ... */


	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tabii yukarıdaki işlemin tersi de benzer biçimde yapılabilmektedir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int a)
{
	printf("foo: %d\n", a);
}

int main(void)
{
	void *pv;		/* pv'de bir fonksiyonun adresinin olduğunu varsayalım */
	void (*pf)(int);

	*(void **)&pf = pv;

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir fonksiyoun geri dönüş değeri bir fonksiyon adresi ise * atomu parantez içerisine alınır, parantezin sı-oluna geri dönüş değerine ilişkin
	fonksiyonun geri dönüş değeri, sağına ise geri dönüş değerine ilişkin fonksiyonun parametre türleri yazılır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int bar(double a)
{
	printf("bar: %f\n", a);

	return 0;
}

int (*foo(void)) (double)
{
	return bar;
}

int main(void)
{
	int (*pf)(double);

	pf = foo();

	pf(1.2);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Geri dönüş değeri fonksiyon göstericisi olan fonksiyonların tanımlanması işlemi typedef bildirimleri ile çok kolaylaşmaktadır
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int bar(double a)
{
	printf("bar: %f\n", a);

	return 0;
}

int (*foo(void)) (double)
{
	return bar;
}

int main(void)
{
	int (*pf)(double);

	pf = foo();

	pf(1.2);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bildirimler daha karmaşık olabilir. Örneğin foo fonksiyonun kendi parametresi void ancak geri dönüş değeri parametresi double geri dönüş değeri
	parametresi long geri dönüş değeri int türden olan bir fonksiyon adresi olsun. Daha açık bir yazarsak biz burada bir foo fonksiyonu yazmak istiyoruz.

	foo

	foo fonksiyonun kendi parametresi void olsun diyoruz:

	foo(void)

	ancak foo fonksiyonun geri dönüş değeri bir fonksiyon adresi olsun istiyoruz:

	(*foo(void))

	Öyle bir fonksiyon adresi olsun ki o fonksiyonun parametresi double türden olsun:

	(*foo(void))(double)

	Ancak foo fonksiyonun geri döndürdüğü fonksiyon adresinin ilişkin olduğu fonksiyonunda geri dönüş değeri bir fonksiyon adresi olsun:

	(*(*foo(void))(double))

	Bu fonksiyonun parametresi long olsun:

	(*(*foo(void))(double))(long)

	ve geri dönüş değeri int olsun:

	int (*(*foo(void))(double))
	{
		....
	}

-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int tar(long a)
{
	printf("tar\n");

	return 0;
}

int (*bar(double a))(long)
{
	return tar;
}

int (*(*foo(void))(double))(long)
{
	printf("foo\n");

	return bar;
}

int main(void)
{
	int (*(*pf1)(double))(long);
	int (*pf2)(long);

	pf1 = foo();
	pf2 = pf1(0);
	pf2(0);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tabii yukarıdaki karmaşık bildirim yine typedef sayesinde daha basit ifade edilebilirdi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

typedef int (*PF1)(long);

int tar(long a)
{
	printf("tar\n");

	return 0;
}

PF1 bar(double a)
{
	return tar;
}

typedef PF1(*PF2)(double);

PF2 foo(void)
{
	printf("foo\n");

	return bar;
}

int main(void)
{
	PF2 pf2;
	PF1 pf1;

	pf2 = foo();
	pf1 = pf2(0);
	pf1(0);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir göstericinin adresi göstericiyi gösteren göstericide saklanabilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int a = 10;
	int *pi;
	int **ppi;

	pi = &a;
	ppi = &pi;

	printf("%d\n", **ppi);

	**ppi = 20;
	printf("%d\n", a);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir gösterici dizisinin ismi onun ilk elemanının adresi olacağına göre göstericiyi gösteren göstericiye atanmalıdır
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	char *names[] = { "ali", "veli", "selami" };
	char **str;

	str = names;

	puts(*str);

	++str;

	puts(*str);

	++str;

	puts(*str);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	C'de parametre parantezi içerisindeki dizisel gösterin tamamen "gösterici" anlamına gelmektedir. Köşeli parantezlerin içeirisndeki sayıların da
	hiçbir önemi yoktur. Dolayısıyla aşağıdaki prototiplerin hepsi aynıdır
-------------------------------------------------------------------------------------------------------------------------------------------*/

void foo(int *a);
void foo(int a[]);
void foo(int a[100]);
void foo(int a[5]);

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyonun parametresi göstericiyi gösterene gösterici ise o parametre yine dizi sentaksıyla belirtilebilir. Dolayısıyla aşağıdaki prototipler
	yine eşdeğerdir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

void bar(int **a);
void bar(int *a[10]);
void bar(int *a[]);

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyon parametresi fonksiyon göstericisi ise o da alternatif biçimde fonksiyon sentaksıyla belirtilebilmektedir. Aşağıdaki iki prototip
	eşdeğerdir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

void tar(int (*a)(double));
void tar(int a(double));

/*------------------------------------------------------------------------------------------------------------------------------------------
	Çok boyutlu diziler aslında C'de dizi dizileri olarak düşünülmelidir. Öneğin:

	int a[3][2];

	Burada a aslında 3 elemanlı bir dizidir. Ancak dizinin her elemanı int[2] türünden yani 2 elemanlı bir int dizidir. İlk köşeli parantez 
	her zaman asıl dizinin u<unluğunu belirtmektedir. Diğer köşeli parantezler eleman olan dizinin türü ile ilgilidir. Bir dizinin ismi dizinin
	eilk elemanın adresini belirttiğine göre yukarıdaki iki boyutlu dizide a ifadesi aslında iki elemanlı bir int dizinin adresini belirtir. 
	Biz C'de dizi isimlerinin adreslerini alabiliriz. Bu durumda elde edilen adres dizi türünden adres olur. Dizi türünden adresler 
	sembolik olarak "tür (*)[uzunuk]" biçiminde ifade edilir. Örneğin:

	int a[2];
	int (*p)[2];

	p = &a;


	Mademki bir dizinin ismi o dizinin ilk elemanın adresini belirtmektedir. O halde aşağıdaki iki boyutlu dizinin ismi hangi türdne adres belirtir?

	int a[3][2];

	Burada a 3 elemanlı, her elemanı 2 elemanlı bir dizi olan dizidir. O halde a ifadesi aslında int (*)[2] türündendir. Örneğin:

	int a[3][2];
	int(*p)[2];

	p = a;

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir dizi göstericisinin gösterdiği yere erişirsek o diziin tamamına erişmiş oluruz. Örneğin:

	int a[3][2];
	int (*pa)[2];

	pa = a;

	Burada pa aslında matrisin ilk elemanı olan iki elemanlı int dizinin tamamını göstermektedir. Dolayısıyla *pa ifadesi aslında 2 elemanlı
	bir int diziyi temsil eder. Tabii bu ifade pa[0] ifadesiyle eşdeğerdir. Burada pa[1] ifadesi bu matrisin ikinci satırını oluşturan 2 elemanlı int diziyi 
	temsil etmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int a[3][2] = { {1, 2}, {3, 4}, {5, 6} };
	int(*pa)[2];

	pa = a;

	printf("%d\n", (*pa)[0]);
	printf("%d\n", (*pa)[1]);

	printf("%d\n", pa[1][0]);
	printf("%d\n", pa[1][1]);

	printf("%d\n", pa[2][0]);
	printf("%d\n", pa[2][1]);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Pekiyi bir matrisi fonksiyona partametre olarak nasıl geçirebiliriz. İşte fonksiyonun parametre değişkeninin bir dizi göstrivisi olması gerekir. 
	Ayrıxa matrisin satır uzunluğunun da fonksiyona aktarılması uygun olur
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int(*pa)[2], size_t size)
{
	size_t i, k;

	for (i = 0; i < size; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", pa[i][k]);
		printf("\n");
	}
}

int main(void)
{
	int a[3][2] = { {1, 2}, {3, 4}, {5, 6} };

	foo(a, 3);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tek boyutlu bir dizi bir dizi göstericisine tür dönüştürme operatörü kullanılarak atanabilir. Bubdan sonra dizi elemanlarına matris sentaksıyla
	erişilebilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };
	int (*b)[2];
	int i, k;

	b = (int(*)[2]) a;

	for (i = 0; i < 3; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", b[i][k]);
		printf("\n");
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir matiris için de dinamik tahsisatlar yapabiliriz. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int(*pa)[2];
	int i, k;

	pa = (int(*)[2]) malloc(5 * sizeof(*pa));
	if (pa == NULL) {
		fprintf(stderr, "cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 5; ++i)
		for (k = 0; k < 2; ++k)
			pa[i][k] = i + k;

	for (i = 0; i < 5; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", pa[i][k]);
		printf("\n");
	}

	free(pa);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	satır sütun uzunluğu belirtilerek bir matrisin genel biçimde fonksiyona aktarılması dizi göstericisi yoluyla mümkün değildir. Bu tür genel
	fonksiyonlar mecburen tek boyutlu diziye indirgeme yapılarak gerçekleştirilir. p T tütünden bir matrisin başlangıç adresini belirten T türünden 
	bir adres olmak üzere matirisn i, k indeksli elemanına p + i * colsize + k ifadesiyle erişilebilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(const int *pi, size_t rowsize, size_t colsize)
{
	size_t i, k;

	for (i = 0; i < rowsize; ++i) {
		for (k = 0; k < colsize; ++k)
			printf("%d ", *(pi + i * colsize + k));
		printf("\n");
	}
}

int main(void)
{
	int a[3][3] = { {1, 2, 3}, {3, 4, 6}, {7, 8, 9} };

	foo((int *)a, 3, 3);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Çok boyutlu dizi göstericileri söz konusu olabilir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int(*pa)[3][9])
{
	/* ... */
}

int main(void)
{
	int a[5][3][9];

	foo(a);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyonun parametre parantezi içerisinde çok boyutlu dizi sentaksı dizi göstericisi anlamına gelmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

void foo(int a[][5])			/* int (*a)[5] */
{
	/* ... */
}

int main(void)
{
	int a[5];

	foo(&a);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyonların geri dönüş değerleri dizi türünden adresler olabilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int(*foo(void))[5]
{
	static int a[3] = {1, 2, 3, 4, 5};

	return &a;
}

int main(void)
{
	int(*pa)[5];
	int i;

	pa = foo();
	for (i = 0; i < 5; ++i)
		printf("%d ", (*pa)[i]);
	printf("\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde prosesin çalışma dizini (current working directory) GetCurrentDirectory API fonksiyonuyla elde edilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char cwd[MAX_PATH];

	if (!GetCurrentDirectory(MAX_PATH, cwd))
		ExitSys("GetCurrentDirectory");

	printf("%s\n", cwd);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	GetCurrentDirectory fonksiyonunda birinci parametre 0, ikinci parametre NULL geçilirse çalışma dizini için gereken karakter uzunluğu (byte değil)
	elde edilir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char *cwd;
	DWORD dwLen;

	if ((dwLen = GetCurrentDirectory(0, NULL)) == 0)
		ExitSys("GetCurrentDirectory");

	if ((cwd = (char *)malloc(dwLen)) == NULL) {
		fprintf(stderr, "Cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	if (!GetCurrentDirectory(dwLen, cwd))
		ExitSys("GetCurrentDirectory");

	printf("%s\n", cwd);

	free(cwd);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}
 
/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde prosesin çalışma dizini getcwd POSIX fonksiyonuyla elde edilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		exit_sys("getcwd");

	puts(cwd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde maksimum path uzunluğu MAX_PATH sembolik sabitiyle belirlenmiştir. Ancak POSIX sistemlerinde böyle bir sembolik sabit yoktur.
	Ancak çalışma zamanı sırasında bu sistemlerde maksimum path uzunluğu elde edilebilir. Aşağıdaki örnekte bunu elde eden path_max isimli bir
	fonksiyon verilmiştir. Ancak bu fonksiyonun nasıl yazıldığı UNIX/Linux Sistem Programlama kursunun konusu içerisindedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void exit_sys(const char *msg);

long path_max(void)
{
	static long result = 0;

#define PATH_MAX_INDETERMINATE_GUESS     4096

#ifdef PATH_MAX
	result = PATH_MAX;
#else
	if (result == 0) {
		errno = 0;
		if ((result = pathconf("/", _PC_PATH_MAX)) == -1 && errno == 0)
			result = PATH_MAX_INDETERMINATE_GUESS;
	}
#endif

	return result;
}

int main(void)
{
	char *cwd;
	long size;

	size = path_max();
	if ((cwd = (char *)malloc(size)) == NULL)
		exit_sys("malloc");

	if (getcwd(cwd, size) == NULL)
		exit_sys("getcwd");

	printf("size: %ld, cwd = %s\n", size, cwd);

	free(cwd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Basit bir shell uygulamasında (cmd.exe benzeri bir shell) GetCurrentDirectory ve SetCurrentDirectory API fonksiyonlarının kullanımı
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_CMD_LINE			4096
#define MAX_CMD_PARAMS			64

struct CMD {
	char *cmd_text;
	void (*proc)(void);
};

void ExitSys(LPCSTR lpszMsg);
void ParseCmdLine(void);
void DirProc(void);
void CopyProc(void);
void ClsProc(void);
void RenameProc(void);
void ChangeDirProc(void);
void DispDirectory(LPCTSTR lpszPath);

char g_cmd_line[MAX_CMD_LINE];
struct CMD g_cmds[] = {
	{"dir", DirProc},
	{"copy", CopyProc},
	{"cls", ClsProc},
	{"rename", RenameProc},
	{"cd", ChangeDirProc},
	{NULL, NULL},
};
char *g_params[MAX_CMD_PARAMS];
int g_nparams;
char g_cwd[MAX_PATH];

int main(void)
{
	char *str;
	int i;

	if (!GetCurrentDirectory(MAX_PATH, g_cwd))
		ExitSys("GetCurrentDirectory");

	for (;;) {
		printf("%s>", g_cwd);
		fgets(g_cmd_line, MAX_CMD_LINE, stdin);
		if ((str = strchr(g_cmd_line, '\n')) != NULL)
			*str = '\0';

		ParseCmdLine();
		if (g_nparams == 0)
			continue;
		if (!strcmp(g_params[0], "exit"))
			break;
		for (i = 0; g_cmds[i].cmd_text != NULL; ++i)
			if (!strcmp(g_cmds[i].cmd_text, g_params[0])) {
				g_cmds[i].proc();
				break;
			}
		if (g_cmds[i].cmd_text == NULL)
			printf("command not found: %s\n\n", g_params[0]);
	}

	return 0;
}

void ParseCmdLine(void)
{
	char *str;

	g_nparams = 0;
	for (str = strtok(g_cmd_line, " \t"); str != NULL; str = strtok(NULL, " \t"))
		g_params[g_nparams++] = str;
	g_params[g_nparams] = NULL;
}

void DirProc(void)
{
	if (g_nparams > 2) {
		printf("too many arguments!..\n");
		return;
	}

	DispDirectory(g_nparams == 1 ? g_cwd : g_params[1]);
}

void CopyProc(void)
{
	if (g_nparams != 3) {
		printf("argument too few or too many!..\n\n");
		return;
	}
}

void ClsProc(void)
{
	if (g_nparams != 1) {
		printf("too many arguments!\n\n");
		return;
	}
	printf("cls command\n");
}

void RenameProc(void)
{
	printf("rename command\n");
}

void ChangeDirProc(void)
{
	if (g_nparams > 2) {
		printf("too many arguments!..\n\n");
		return;
	}

	if (g_nparams == 1) {
		printf("%s\n\n", g_cwd);
		return;
	}

	if (!SetCurrentDirectory(g_params[1])) {
		printf("directory not found or cannot change: %s\n\n", g_params[1]);
		return;
	}

	if (!GetCurrentDirectory(MAX_PATH, g_cwd))
		ExitSys("GetCurrentDirectory");
}

void DispDirectory(LPCTSTR lpszPath)
{
	WIN32_FIND_DATA wfd;
	char lpszDirPath[MAX_PATH];
	HANDLE hFF;

	sprintf(lpszDirPath, "%s/*.*", lpszPath);
	if ((hFF = FindFirstFile(lpszDirPath, &wfd)) == INVALID_HANDLE_VALUE) {
		printf("directory not found or cannot display!\n\n");
		return;
	}

	do {
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			printf("%-10s", "<DIR>");
		else
			printf("%-10lu", wfd.nFileSizeLow);

		printf("%s\n", wfd.cFileName);
	} while (FindNextFile(hFF, &wfd));

	printf("\n");
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde proseslerin çalışma dizinleri chdir isimli POSIX fonksiyonuyla değiştirilir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		exit_sys("getcwd");

	puts(cwd);

	if (chdir("/usr/include") == -1)
		exit_sys("getcwd");

	if (getcwd(cwd, 4096) == NULL)
		exit_sys("getcwd");

	puts(cwd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Özyinelemeye tipik bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void foo(int a)
{
	printf("Giriş: a = %d\n", a);

	if (a == 0)
		return;

	foo(a - 1);

	printf("Çıkış: a = %d\n", a);
}

int main(void)
{
	foo(5);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Faktöriyel hesabı yapan iteratif fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

unsigned long factorial(int n)
{
	unsigned long f = 1;
	int i;

	for (i = 2; i <= n; ++i)
		f *= i;

	return f;
}

int main(void)
{
	unsigned long result;

	result = factorial(2);
	printf("%lu\n", result);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Faktöriyel hesabı yapan özyinelemeli fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

unsigned long long factorial(int n)
{
	if (n == 0)
		return 1;

	return n * factorial(n - 1);
}

int main(void)
{
	unsigned long long result;

	result = factorial(6);
	printf("%llu\n", result);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yazıyı tersten yazdıran iteratif fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void putsrev(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
		;

	for (--i; i >= 0; --i)
		putchar(str[i]);

	putchar('\n');
}

int main(void)
{
	putsrev("ankara");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yazıyı tersten yazdıran özyinelemeli fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void putsrev(const char *str)
{
	if (*str == '\0')
		return;

	putsrev(str + 1);
	putchar(*str);
}

int main(void)
{
	putsrev("ankara");
	putchar('\n');

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yazıyı iteratif yolla ters çeviren fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void revstr(char *str)
{
	size_t n, i;
	char temp;

	for (n = 0; str[n] != '\0'; ++n)
		;

	for (i = 0; i < n / 2; ++i) {
		temp = str[n - 1 - i];
		str[n - 1 - i] = str[i];
		str[i] = temp;
	}
}

int main(void)
{
	char s[] = "ankara";

	revstr(s);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki fonksiyonun iteratif olarak başka bir yazım biçimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

void revstr(char *str, size_t left, size_t right)
{
	char temp;

	while (left < right) {
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left, --right;
	}
}

int main(void)
{
	char s[] = "ankara";

	revstr(s, 0, strlen(s) - 1);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki fonksiyonun özyinelemeli biçimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

void revstr(char *str, size_t left, size_t right)
{
	char temp;

	while (left >= right)
		return;

	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr(str, left + 1, right - 1);
}

int main(void)
{
	char s[] = "ankara";

	revstr(s, 0, strlen(s) - 1);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bazen özyinelemeli fonksiyonun parametrik yapısı kolay kullanıma izin veremeyebilir. Bu durumda programcı bir sarma fonksiyon(wrapper function)
	yazarak özyinelemeli fonksiyonu çağırır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void revstr_recur(char *str, size_t left, size_t right)
{
	char temp;

	while (left >= right)
		return;

	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr_recur(str, left + 1, right - 1);
}

void revstr(char *str)
{
	size_t i;

	if (*str == '\0')
		return;

	for (i = 0; str[i] != '\0'; ++i)
		;

	revstr_recur(str, 0, i - 1);
}

int main(void)
{
	char s[] = "ankara";

	revstr(s);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir int sayıyı binary olarak iteratif biçimde ekrana yazdıran fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void binprint(unsigned int n)
{
	int i;

	for (i = sizeof(n) * 8 - 1; i >= 0; --i)
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void)
{
	binprint(21);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki fonksiyonun baştaki 0'ları yazdırmayan biçimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void binprint(unsigned int n)
{
	int i;

	for (i = sizeof(n) * 8 - 1; i >= 0; --i)
		if (n >> i & 1)
			break;

	for (; i >= 0; --i)
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void)
{
	binprint(21);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki fonksiyonun özyinelemeli biçimi aşağıdaki gibi yazılabilir. Özyineleme düz olan bir şeyi tersten yaptırmak için de çok kullanılmaktadır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void binprint(unsigned int n)
{
	if (n == 0)
		return;
	binprint(n >> 1);

	putchar((n & 1) + '0');
}

int main(void)
{
	binprint(21);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Bir tamsayının yalnızca putchar fonksiyonu kullanılarak ekrana yazdırılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

void putint(long long n)
{
	char s[32];
	int i, nflag;

	nflag = 0;
	if (n < 0) {
		n = -n;
		nflag = 1;
	}
	i = (int)log10(n) + 1 + nflag;
	s[i--] = '\0';

	while (n) {
		s[i--] = n % 10 + '0';
		n /= 10;
	}
	if (nflag)
		s[i] = '-';

	for (i = 0; s[i] != '\0'; ++i)
		putchar(s[i]);
	putchar('\n');
}

int main(void)
{
	putint(-1234);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki işlemin özyinelemeli biçimi. Burada özyineleme ters olan bir şeyi düz hale getirmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void putint(long long n)
{
	if (n < 0) {
		n = -n;
		putchar('-');
	}

	if (n / 10)
		putint(n / 10);

	putchar(n % 10 + '0');
}

int main(void)
{
	putint(-1234);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki fonksiyonun herhangi bir tabana göre genelleştirilmiş biçimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void putint(long long n, int base)
{
	if (n < 0) {
		n = -n;
		putchar('-');
	}

	if (n / base)
		putint(n / base, base);

	putchar(n % base > 9 ? n % base - 10 + 'A' : n % base + '0');
	/* putchar((n % base > 9 ? -10 + 'A' : '0') + n % base); */
}

int main(void)
{
	putint(123, 10);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Kapalı bir şeklin içinin boyanması için floodfill algoritması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

char g_bitmap[10][22];

int read_bitmap(const char *path)
{
	FILE *f;
	int i;

	if ((f = fopen(path, "r")) == NULL)
		return 0;

	for (i = 0; i < 10; ++i)
		fgets(g_bitmap[i], 22, f);

	fclose(f);

	return 1;
}

void floodfill(int row, int col, int ch)
{
	if (g_bitmap[row][col] == '#' || g_bitmap[row][col] == ch)
		return;

	g_bitmap[row][col] = ch;

	floodfill(row - 1, col, ch);
	floodfill(row, col + 1, ch);
	floodfill(row + 1, col, ch);
	floodfill(row, col - 1, ch);
}

void disp_bitmap(void)
{
	int row, col;

	for (row = 0; row < 10; ++row) {
		for (col = 0; col < 20; ++col)
			putchar(g_bitmap[row][col]);
		putchar('\n');
	}
}

int main(void)
{
	if (!read_bitmap("bitmap.txt")) {
		fprintf(stderr, "cannot read bitmap!..\n");
		exit(EXIT_FAILURE);
	}

	floodfill(5, 5, '.');

	disp_bitmap();

	return 0;
}

/*
			 #######
		#####      #
 #######      ######
 #                 #
 #                 #
 #            ######
 ###          #
	#####     #
		 ##   #
		   ###

*/

/*------------------------------------------------------------------------------------------------------------------------------------------
	Seçerek sıralama (selection sort) algoritmasının iteratif yazımı
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void ssort(int *pi, size_t size)
{
	size_t i, k;
	size_t min_index;
	int min;

	for (i = 0; i < size - 1; ++i) {
		min_index = i;
		min = pi[i];
		for (k = i + 1; k < size; ++k)
			if (pi[k] < min) {
				min = pi[k];
				min_index = k;
			}
		pi[min_index] = pi[i];
		pi[i] = min;
	}
}

void disp(const int *pi, size_t size)
{
	size_t i;

	for (i = 0; i < size; ++i)
		printf("%d ", pi[i]);
	printf("\n");
}

#define SIZE		10

int main(void)
{
	int a[SIZE] = { 34, 12, 7, 84, 72, 39, 75, 45, 59, 21 };

	ssort(a, SIZE);
	disp(a, SIZE);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Seçerek sıralama algoritmasının özyinelemeli uygulanması (bu algoritma için özyineleme kötü bir teknik)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void ssort(int *pi, size_t size)
{
	size_t max_index, i;
	int max;

	if (size == 1)
		return;

	max = pi[0];
	max_index = 0;

	for (i = 1; i < size; ++i)
		if (pi[i] > max) {
			max = pi[i];
			max_index = i;
		}

	pi[max_index] = pi[size - 1];
	pi[size - 1] = max;

	ssort(pi, size - 1);
}

void disp(const int *pi, size_t size)
{
	size_t i;

	for (i = 0; i < size; ++i)
		printf("%d ", pi[i]);
	printf("\n");
}

#define SIZE		10

int main(void)
{
	int a[SIZE] = { 34, 12, 7, 84, 72, 39, 75, 45, 59, 21 };

	ssort(a, SIZE);
	disp(a, SIZE);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	8 vezir problemi bir satranç tahtasına birbirini yemeyen 8 vezirin yerleştirilmesi problemidir. Özyinelemeli bir çözüm gerektirir. Tipik çözümde
	tahta global bir matris olarak organize edilir. İlk boş yere vezir yerleştirilir. Vezirin etki alanı matriste işaretlenir ve fonksiyon kendisini 
	çağırır. Böylece yeni çağrımda da ilk boş yer bulunup aynı şeyler yapılacaktır. Tahta dolduğunda fonksiyon sonlandırılır. 8 değeri elde edildiğinde
	tahta print edilir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#define SIZE		8

int g_qcount;
int g_count;
char g_board[SIZE][SIZE];

void init_board(void)
{
	int r, c;

	for (r = 0; r < SIZE; ++r)
		for (c = 0; c < SIZE; ++c)
			g_board[r][c] = '.';
}

void print_board(void)
{
	int r, c;

	printf("%d\n", g_count);

	for (r = 0; r < SIZE; ++r) {
		for (c = 0; c < SIZE; ++c)
			printf("%c", g_board[r][c]);
		printf("\n");
	}
	printf("\n");
}

void locate_queen(int row, int col)
{
	int r, c;

	g_board[row][col] = 'V';

	r = row;
	for (c = col + 1; c < SIZE; ++c)
		g_board[r][c] = 'o';
	for (c = col - 1; c >= 0; --c)
		g_board[r][c] = 'o';
	c = col;
	for (r = row - 1; r >= 0; --r)
		g_board[r][c] = 'o';
	for (r = row + 1; r < SIZE; ++r)
		g_board[r][c] = 'o';
	for (r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c)
		g_board[r][c] = 'o';
	for (r = row - 1, c = col + 1; r >= 0 && c < SIZE; --r, ++c)
		g_board[r][c] = 'o';
	for (r = row + 1, c = col - 1; r < SIZE && c >= 0; ++r, --c)
		g_board[r][c] = 'o';
	for (r = row + 1, c = col + 1; r < SIZE && c < SIZE; ++r, ++c)
		g_board[r][c] = 'o';
}

void queen8(int row, int col)
{
	char board[SIZE][SIZE];
	int r, c;

	for (; row < SIZE; ++row) {
		for (; col < SIZE; ++col) {
			if (g_board[row][col] == '.') {
				for (r = 0; r < SIZE; ++r)
					for (c = 0; c < SIZE; ++c)
						board[r][c] = g_board[r][c];

				++g_qcount;
				locate_queen(row, col);

				if (g_qcount == SIZE) {
					++g_count;
					print_board();
				}

				queen8(row, col);
				--g_qcount;

				for (r = 0; r < SIZE; ++r)
					for (c = 0; c < SIZE; ++c)
						g_board[r][c] = board[r][c];
			}
		}
		col = 0;
	}
}

int main(void)
{
	init_board();
	queen8(0, 0);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta dizin ağacını dolaşan özyinelemeli fonksiyon
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void WalkDir(LPCSTR lpszPath)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath))
		return;

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%s\n", wfd.cFileName);
			WalkDir(wfd.cFileName);
			if (!SetCurrentDirectory(".."))
				break;
		}

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);
}

int main(void)
{
	WalkDir("f:\\Dropbox\\Kurslar\\SysProg-1");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows'ta UNIX/Linux sistemlerinde olduğu gibi bazı dizinlere prosesin geçişh hakkı (yani SetCurrentDirectory yapma hakkı) olmayabilir. 
	Bu duurmu da rapor edebiliriz. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void PutErrMsg(LPCSTR lpszMsg);

void WalkDir(LPCSTR lpszPath)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		PutErrMsg(lpszPath);
		return;
	}

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%s\n", wfd.cFileName);
			WalkDir(wfd.cFileName);
			if (!SetCurrentDirectory("..")) {
				PutErrMsg("..");
				break;
			}
		}

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

int main(void)
{
	WalkDir("f:\\dropbox\\kurslar\\sysprog-1");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Dizinleri dolaşırken onları kademeli bir biçimde ekrana yazdırdabiliriz. Geçemediğimiz dizinler :xxxx: biçiminde gösterilmiştir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TABSIZE		4

void PutErrMsg(LPCSTR lpszMsg);

void WalkDir(LPCSTR lpszPath, int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		printf("%*s:%s:\n", level * TABSIZE, "", lpszPath);
		return;
	}

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%*s%s\n", level * TABSIZE, "", wfd.cFileName);
			WalkDir(wfd.cFileName, level + 1);
			if (!SetCurrentDirectory(".."))
				break;
		}
	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);
}

int main(void)
{
	WalkDir("c:\\", 0);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki WalkDir fonksiyonlarında önemli bir kusur fonksiyonun prosesin çalışma dizinini değiştirerek işini sonlandırmasıdır. 
	Fonksiyonun çağrılmadan önceki çalışma dizinini yeniden set etmesi için bir sarma fonksiyon kullanılabilir. (access POSIX fonksiyonu
	Windows sistemlerinde _access ismiyle de bulunmaktadır.)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>

#define TABSIZE		4

void PutErrMsg(LPCSTR lpszMsg);

void WalkDirRecur(LPCSTR lpszPath, int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		printf("%*s:%s:\n", level * TABSIZE, "", lpszPath);
		return;
	}

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%*s%s\n", level * TABSIZE, "", wfd.cFileName);
			WalkDirRecur(wfd.cFileName, level + 1);
			if (!SetCurrentDirectory(".."))
				break;
		}

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);
}

void WalkDir(LPCSTR lpszPath)
{
	char cwd[MAX_PATH];

	if (_access(lpszPath, 0)) {
		fprintf(stderr, "Path not found: %s\n", lpszPath);
		return;
	}

	if (!GetCurrentDirectory(MAX_PATH, cwd))
		PutErrMsg("GetCurrentDirectory");

	WalkDirRecur(lpszPath, 0);

	if (!SetCurrentDirectory(cwd))
		PutErrMsg("SetCurrentDirectory");
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

int main(void)
{
	WalkDir("f:\\dropbox\\kurslar\\sysprog-1");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Dizin ağacını dolaşırken bulun dizin girişlerini ekrana yazdırmak yerine başka bir şey yapmak isteyebiliriz. Böyle bir fonksiyonun genelleştirilmesi
	için fonksiyon göstericilerinden faydalanılabilir. Aşağıdaki örnekte dizin ağacını dolaşan fonksiyon her dizin girişini bulduğunda call-back
	bir fonksiyon çağırmaktadır. Öağrılan bu fonksiyon TRUE ile geri döndüğünde dolaşıma devam edilmekte FALSE ile geri döndüğünde dolaşım sonlandırılarak
	çıkış sağlanmaktadır. Dizin ağacını dolaşan fonksiyon erken sonlanmışsa FALSE ile normal sonlanmışsa TRUE ile geri dönmektedir. Koddaki _access ve _strcmpi
	fonksiyonları standart olmayan fonksiyonlardır. Microsoft standart olmayan ve API fonksiyonu da olmayan fonksiyonları _ ile başlayarak isimlendirmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>

void PutErrMsg(LPCSTR lpszMsg);

BOOL WalkDirRecur(LPCSTR lpszPath, BOOL(*Proc)(const WIN32_FIND_DATA *, int), int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	BOOL result;

	result = TRUE;
	if (!SetCurrentDirectory(lpszPath))
		return;

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!Proc(&wfd, level)) {
			result = FALSE;
			break;
		}

		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!WalkDirRecur(wfd.cFileName, Proc, level + 1)) {
				result = FALSE;
				break;
			}

			if (!SetCurrentDirectory(".."))
				break;
		}

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);

	return result;
}

BOOL WalkDir(LPCSTR lpszPath, BOOL(*Proc)(const WIN32_FIND_DATA *, int))
{
	char cwd[MAX_PATH];
	BOOL result;

	if (_access(lpszPath, 0)) {
		fprintf(stderr, "Path not found: %s\n", lpszPath);
		return;
	}

	if (!GetCurrentDirectory(MAX_PATH, cwd))
		PutErrMsg("GetCurrentDirectory");

	result = WalkDirRecur(lpszPath, Proc, 0);

	if (!SetCurrentDirectory(cwd))
		PutErrMsg("SetCurrentDirectory");

	return result;
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

BOOL Proc(const WIN32_FIND_DATA *wfd, int level)
{
	printf("%*s%s %s\n", level * 4, "", wfd->cFileName, wfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : "");

	if (!_strcmpi(wfd->cFileName, "sample.c"))
		return FALSE;

	return TRUE;
}

int main(void)
{
	BOOL result;

	result = WalkDir("f:\\dropbox\\kurslar\\sysprog-1", Proc);

	printf("%s\n", result ? "\nFonksiyon ağacı tamamen dolaştı\n" : "Fonksiyon erken sonlandı\n");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde dizin ağacının dolaşılması
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void walkdir(const char *path)
{
	DIR *dir;
	struct dirent *ent;
	struct stat finfo;

	if (chdir(path) == -1)
		return;

	if ((dir = opendir(".")) == NULL)
		return;

	while ((ent = readdir(dir)) != NULL) {
		printf("%s\n", ent->d_name);

		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue;

		if (lstat(ent->d_name, &finfo) == -1)
			continue;

		if (S_ISDIR(finfo.st_mode)) {
			walkdir(ent->d_name);
			if (chdir("..") == -1)
				break;
		}
	}

	closedir(dir);
}

int main(void)
{
	walkdir(".");

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki programı kademeli yazacak hale getirebiliriz
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define TABSIZE		4

void walkdir(const char *path, int level)
{
	DIR *dir;
	struct dirent *ent;
	struct stat finfo;

	if (chdir(path) == -1)
		return;

	if ((dir = opendir(".")) == NULL)
		return;

	while ((ent = readdir(dir)) != NULL) {
		printf("%*s%s\n", level * TABSIZE, "", ent->d_name);

		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue;

		if (lstat(ent->d_name, &finfo) == -1)
			continue;

		if (S_ISDIR(finfo.st_mode)) {
			walkdir(ent->d_name, level + 1);
			if (chdir("..") == -1)
				break;
		}
	}

	closedir(dir);
}

int main(void)
{
	walkdir(".", 0);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Fonksiyonun prosesin çalışma dizinini geri set eden sarmalı biçimi şöyle olabilir
-------------------------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define TABSIZE		4

void walkdir_recur(const char *path, int level)
{
	DIR *dir;
	struct dirent *ent;
	struct stat finfo;

	if (chdir(path) == -1)
		return;

	if ((dir = opendir(".")) == NULL)
		return;

	while ((ent = readdir(dir)) != NULL) {
		printf("%*s%s\n", level * TABSIZE, "", ent->d_name);

		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue;

		if (lstat(ent->d_name, &finfo) == -1)
			continue;

		if (S_ISDIR(finfo.st_mode)) {
			walkdir_recur(ent->d_name, level + 1);
			if (chdir("..") == -1)
				break;
		}
	}

	closedir(dir);
}

void walkdir(const char *path)
{
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		perror("getcwd");

	walkdir_recur(path, 0);

	if (chdir(cwd) == -1)
		perror("chdir");
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	walkdir(argv[1]);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Hizalama en çok bir dosyanın içerisindeki bilgilerin bir yapıya okunacağı zaman çıkar. Aşağıdaki örnekte eğer hizalama byte hizalamasına
	çekilmezse bimap dosyanın başlık kısmındaki bilgiler yapı elemanlarına tam orturmaz.
-------------------------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(1)

struct BITMAP_HEADER {
	char magic[2];			/* 2 byte */
	uint32_t size;			/* 4 byte */
	uint16_t reserved1;		/* 2 byte */
	uint16_t reserved2;		/* 2 byte */
	uint32_t dataloc;		/* 4 byte */
};

#pragma pack(4)

int main(void)
{
	FILE *f;
	struct BITMAP_HEADER bh;

	if ((f = fopen("test.bmp", "rb")) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	fread(&bh, sizeof(struct BITMAP_HEADER), 1, f);

	printf("Magic: %c%c\n", bh.magic[0], bh.magic[1]);
	printf("Size: %u\n", bh.size);
	printf("Bitmap Data Locatiion: %u\n", bh.dataloc);

	fclose(f);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yapı elemanların sırası hizalama boşlukları üzerinde etkili olmaktadır. Derleyiciler hçbir zaman yapı elemanlarının yerlerini optimizasyon amacıyla
	değiştirmezler. (Çünkü C ve C++ standartlarınca yapıların elemanlarının ilk yazlan düşük adreste olacak biçimde ardışıl dizildiği belirtilmektedir. 
	Padding byte'lar kontrollü olduğu için ardışıllığı bozmamaktadır.)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct SAMPLE1 {
	char a;
	int b;
	char c;
	int d;
};

struct SAMPLE2 {
	char a;
	char c;
	int b;
	int d;
};

int main(void)
{
	struct SAMPLE1 s;
	struct SAMPLE1 k;

	printf("%u\n", sizeof(s));
	printf("%u\n", sizeof(k));


	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Read only LFU Algoritmasını kullanan basit bir önbellek sisteminin gerçekleştirilmesi
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* filecache.h */

#ifndef FILECACHE_H_
#define FILECACHE_H_

/* Symbolic Constants */

#define LINE_SIZE               32
#define NCACHE_LINES            10
#define INITIAL_COUNT           2

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...)  fprintf(stderr, fmt, ## __VA_ARGS__)     
#else
#define DEBUG_PRINT(fmt, ...)       
#endif

/* Type Definitions */

typedef struct tagCACHELINE {
	char buf[LINE_SIZE];
	int blockno;
	size_t count;
} CACHE_LINE;

typedef struct tagCACHE {
	int fd;
	CACHE_LINE clines[NCACHE_LINES];
	size_t tcount;
} CACHE, *HCACHE;

/* Function Prototypes */

HCACHE open_file(const char *path, int flags);
int read_file(HCACHE hc, int blockno, void *buf);
int close_file(HCACHE hc);

#endif

/* filecahe.c */

#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filecache.h"

#ifdef DEBUG
static void print_cline_counts(HCACHE hc);
#endif

static size_t select_line(HCACHE hc);

HCACHE open_file(const char *path, int flags)
{
	HCACHE hc;
	int i;

	if ((hc = (HCACHE)malloc(sizeof(CACHE))) == NULL)
		return NULL;

	if ((hc->fd = open(path, flags)) == -1) {
		free(hc);
		return NULL;
	}

	for (i = 0; i < NCACHE_LINES; ++i) {
		hc->clines[i].blockno = -1;
		hc->clines[i].count = 0;
	}
	hc->tcount = 0;

	return hc;
}

int read_file(HCACHE hc, int blockno, void *buf)
{
	int i;
	int rline;

	for (i = 0; i < NCACHE_LINES; ++i)
		if (hc->clines[i].blockno == blockno) {
			DEBUG_PRINT("Cache hit block %d, used cache line %d\n", blockno, i);

			memcpy(buf, hc->clines[i].buf, LINE_SIZE);
			++hc->clines[i].count;
			++hc->tcount;

#ifdef DEBUG
			print_cline_counts(hc);
#endif

			return 0;
		}

	rline = select_line(hc);

	if (lseek(hc->fd, (off_t)blockno * LINE_SIZE, SEEK_SET) == -1)
		return -1;
	if (read(hc->fd, hc->clines[rline].buf, LINE_SIZE) == -1)
		return -1;
	hc->clines[rline].blockno = blockno;

	hc->clines[rline].count = hc->tcount / NCACHE_LINES + 1;
	hc->tcount += hc->clines[rline].count;

	memcpy(buf, hc->clines[rline].buf, LINE_SIZE);

	DEBUG_PRINT("Cache miss block %d, used cache line %d\n", blockno, rline);

#ifdef DEBUG
	print_cline_counts(hc);
#endif

	return 0;
}

int close_file(HCACHE hc)
{
	close(hc->fd);

	DEBUG_PRINT("Cache closed!\n");

	free(hc);
}

static size_t select_line(HCACHE hc)
{
	size_t min_count;
	size_t min_index;
	int i;

	min_count = hc->clines[0].count;
	min_index = 0;

	for (i = 1; i < NCACHE_LINES; ++i) {
		if (hc->clines[i].count < min_count) {
			min_count = hc->clines[i].count;
			min_index = i;
		}
	}

	return min_index;
}

#ifdef DEBUG

static void print_cline_counts(HCACHE hc)
{
	int i;

	putchar('\n');
	printf("Total count: %llu\n", (unsigned long long)hc->tcount);
	for (i = 0; i < NCACHE_LINES; ++i)
		printf("Cachle Line %d --> Block: %d, Count: %llu\n", i, hc->clines[i].blockno, (unsigned long long)hc->clines[i].count);

	putchar('\n');
}

#endif

/* filecache-test.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include "filecache.h"

int create_test_file(const char *path, int nblocks);

int main(int argc, char *argv[])
{
	HCACHE hc;
	char buf[32 + 1];
	int blockno;

#ifdef CREATE
	if (create_test_file("test.dat", 100) == -1) {
		perror("create_test_file");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
#endif

	if ((hc = open_file("test.dat", O_RDONLY)) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		printf("Block No:");
		scanf("%d", &blockno);
		putchar('\n');
		if (blockno == -1)
			break;

		if (read_file(hc, blockno, buf) == -1) {
			perror("read_file");
			exit(EXIT_FAILURE);
		}
		buf[32] = '\0';
		printf("Block content: %s\n\n", buf);
	}

	close_file(hc);


	return 0;
}

int create_test_file(const char *path, int nblocks)
{
	FILE *f;
	int i, k;
	char buf[LINE_SIZE];

	srand(time(NULL));
	if ((f = fopen(path, "wb")) == NULL)
		return -1;

	for (i = 0; i < nblocks; ++i) {
		sprintf(buf, "%04d ", i);
		for (k = 5; k < 32; ++k)
			buf[k] = rand() % 26 + 'A';

		if (fwrite(buf, LINE_SIZE, 1, f) != 1)
			return -1;
	}

	fclose(f);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
    Büyük bir dosyayı Windows'ta ReadFile API fonksiyonuyla, UNIX/Linux sistemlerinde read fonksiyonuyla byte bu-yte okumak iyi bir teknk
    değildir. Çünkü böyle bir uygulamada proses her defasında sistem fonksiyonun çağrılması nedeni ile "kernel moda" geçecektir. Aşaüıda
    POSIX sistemlerinde 5 MB civarı bir dosya read fonksiyonuyla byte byte okunmuş ve bu işlemin ne kadar zaman aldığı hesaplanmıştır.
    Apple Macbook Pro M1 SOC'un kullanıldığı MAc OS X sistemlerinde bu zaman yaklaşık 1.45 saniye civarındadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    int fd;
    char ch;
    ssize_t result;
    size_t count;
    clock_t t1, t2;
    double ts;

    t1 = clock();

    if ((fd = open("/Users/KaanAslan/Study/SysProg/test.dat", O_RDONLY)) == -1)
        exit_sys("open");

    while ((result = read(fd, &ch, 1)) > 0)
        ;
    if (result == -1)
        exit_sys("read");

    close(fd);

    t2 = clock();

    ts = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", ts);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
    C'nin standart dosya fonksiyonları her açılan dosya için bir önbellek oluşturmaktadır. Böylece biz dosyaan okuma yaptığımızda aslında standart C fonksiyonları
    POSIX read fonksiyonunu ya da Windows'un ReadFile fonksiyonunu çağırıp bu önbelleği doldurmaktadır. Sonraki okumalarda yeniden bu fonksiyonları
    çağırmadan mümkğn olduğunca bize isteğimiz bilgileri hızlı bir biçimde önbellekten vermektedir. Buradaki önbelleğe C dünyasında "tampon (bug-ffer)"
    da denilmektedir. Bu tamponlamanın (yani önbellek sisteminin) amacı işletim sisteminin sistem fonksiyonlarının daha az çağrılmasını sağlamaktır.
    Bu önbellek sistemini işletim sisteminin oluşturduğu disk önbellek sistemi ile karıştırmayınız.İşletim sistemi diske erişimi azaltmak için önbeellek sistemi
    oluştururken standart C fonksiyonlarının önbellek sistemi işletim sisteminin sistem fonksiyonlarının daha az çağrılmasını sağlamaktadır.

    Aşağıdaki kodda aynı dosya (5 MB civarında) bu kez standart fgetc fonksiyonuyla byte buyte okunmuşturi Ortalama zaman 0.1 saniye civarındadır.
    Bu da işlemin 15 kat daha hızlı yapıldığı anlamına gelmektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    FILE *f;
    int ch;
    clock_t t1, t2;
    double ts;

    t1 = clock();

    if ((f = fopen("/Users/KaanAslan/Study/SysProg/test.dat", "rb")) == NULL) {
        fprintf(stderr, "Cannot open file!..\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(f)) != EOF)
        ;

    fclose(f);

    t2 = clock();

    ts = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", ts);

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
    C'nin stdio fonksiyonları read/write bir cache (tampon) kullanmaktadır. Dolayısıyla bizim dosyaya yazdığımız şeyler aslında tampona yazılmaktadır.
    Bu tampon da ya başka bilgi tampona aktarılırken dosyaya yazılır ya da fflush işlemi sırasında dosyaya yazılır. exit standart C fonksiyonu
    prosesi sonlandırmadan önce fopen ile açılmış olamn bütün dosyaları fclose ile kapatmaktadır. fclose ise dosyayı önce fflsuh ile flush eder.
    Aşağıdaki örnekte proses standart exit fonksiyonuyla değil POSIX'in _exit fonksiyomuyla sonlandırılmıştır. Dolayısıyşla dosyaya yazılanlar
    flush edilemeyecektir.

    Biz C'de hiç exit fonksiyonunu çağırmasak biel zaten main bitince exit fonksiyonu çağrılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    FILE *f;

    if ((f = fopen("test.txt", "w")) == NULL) {
        fprintf(stderr, "Cannot open file!..\n");
        exit(EXIT_FAILURE);
    }

    fputc('a', f);
    fputc('b', f);
    fputc('\n', f);

    _exit(0);

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	fdopen isimli POSIX fonksiyonun kullanımı
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	int fd;
	ssize_t result;
	FILE *f;
	char buf[10 + 1];
	int ch;

	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if ((result = read(fd, buf, 10)) == -1)
		exit_sys("read");

	buf[result] = '\0';
	printf("read ile okunan byte'lar: %s\n", buf);

	if ((f = fdopen(fd, "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(f)) != EOF)
		putchar(ch);

	if (ferror(f)) {
		fprintf(stderr, "cannot read file!..\n");
		exit(EXIT_FAILURE);
	}

	fclose(f);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	setbuf fonksiyonu dosya için ayrılan tamponun yerini değiştirmek için kullanılmaktadır. Bu fonksiyon tamponun boyutunu değiştirmez, BUFSIZ 
	büyüklüğündeki tamponun yerini değiştirir. Fakat bu fonksiyon aynı zamanda ikinci parametre iin NULL adres girilirse dosyayı sıfır tamponlamalı 
	(no buffered) moda da sokmaktadır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void disp_hex(const void *buf, size_t size, size_t lbytes)
{
	size_t i, k, remainder;
	unsigned char *cbuf = (unsigned char *)buf;

	for (i = 0; i < size; ++i) {
		if (i % lbytes == 0)
			printf("%08x ", (unsigned int)i);

		printf("%02X ", cbuf[i]);

		if (i % lbytes == lbytes - 1) {
			for (k = 0; k < lbytes; ++k)
				printf("%c", iscntrl(cbuf[i - lbytes + k]) ? '.' : cbuf[i - lbytes + k]);
			putchar('\n');
		}
	}

	remainder = size % lbytes;
	for (k = 0; k < 3 * (lbytes - remainder); ++k)
		putchar(' ');

	for (k = 0; k < remainder; ++k)
		printf("%c", iscntrl(cbuf[i - remainder + k]) ? '.' : cbuf[i - remainder + k]);
	putchar('\n');
}

int main(void)
{
	FILE *f;
	char buf[BUFSIZ];

	if ((f = fopen("test.txt", "r+")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	setbuf(f, buf);

	fgetc(f);

	disp_hex(buf, BUFSIZ, 16);

	printf("---------------------------------------------\n");

	fputc('x', f);
	disp_hex(buf, BUFSIZ, 16);

	fclose(f);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	setvbuf fonksiyonu setbuf fonksiyonundan daha yeteneklidir. Çünkü bu fonksiyonla biz hem tamponun yerini, hem büyüklüğünü hem de tamponlama stratejisini
	değiştrebiliriz. Aşağıdaki örnekte dosyanın tampon 64 byte'a düşürülmüştür ve dosya Line buffered moda sokulmuştur. Her ne kadar line buffered modda
	tampon bir satır kadar bilgiyle dolduruluyorsa da kütüphaneler yine okuma sırasında tamponun tamamını doldurabilmektedir. Ancak yazma sırasında kesinlikle
	'\n' karakteri tampona yazıldığında tampon tazelenir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void disp_hex(const void *buf, size_t size, size_t lbytes)
{
	size_t i, k, remainder;
	unsigned char *cbuf = (unsigned char *)buf;

	for (i = 0; i < size; ++i) {
		if (i % lbytes == 0)
			printf("%08x ", (unsigned int)i);

		printf("%02X ", cbuf[i]);

		if (i % lbytes == lbytes - 1) {
			for (k = 0; k < lbytes; ++k)
				printf("%c", iscntrl(cbuf[i - lbytes + k]) ? '.' : cbuf[i - lbytes + k]);
			putchar('\n');
		}
	}

	remainder = size % lbytes;
	for (k = 0; k < 3 * (lbytes - remainder); ++k)
		putchar(' ');

	for (k = 0; k < remainder; ++k)
		printf("%c", iscntrl(cbuf[i - remainder + k]) ? '.' : cbuf[i - remainder + k]);
	putchar('\n');
}

int main(void)
{
	FILE *f;
	char buf[64] = { '\0' };

	if ((f = fopen("test.txt", "r+b")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	setvbuf(f, buf, _IOLBF, 64);
	fgetc(f);

	disp_hex(buf, 64, 16);

	fclose(f);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Klavye ve ekran "terminal aygıt sürücüsü" biçiminde isimlendirilen bir aygıt sürücü tarafından kontrol edilmektedir. Dolayısıyla aslında biz 
	ekrana bir şey yazmak istediğimizde bu aygıt sürücüyü açıp ona bir şeyler yazarız. Bizim aygıt sürücüye yazdığımız şeyleri aygıt sürücü ekrana yazdırmaktadır. 
	Aynı durum klavyeden okuma yaparken de söz konusudur. Aşağıda Linuz sistemlerinde pseudo terminal aygıt sürücü yoluyla açılıp bir şeyler yazılmıştır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	int fd;

	if ((fd = open("/dev/pts/0", O_WRONLY)) == -1)
		exit_sys("open");

	write(fd, "ankara", 6);

	close(fd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde bir proses yaratıldığında aten 0, 1 ve 2 numaralı betimleyiciler açık bir biçimde proses başlar. 0 numaralı betimleyici
	terminale ilişkin aygıt sürücüsünü girdi elde etmek için, 1 numaralı dosya betimleyicisi çıktı oluşturmak için temsil etmektedir. 2 numaralı betimleyici
	de stderr dosyasını temsil eder. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	char buf[4096];
	ssize_t result;

	if ((result = read(0, buf, 1024)) == -1)
		exit_sys("read");

	if (write(1, buf, result) == -1)
		exit_sys("write");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Benzer biçimde Windows'ta da bir proses yaratıldığında terminal aygıt sürücülerine ilişkin dosya HANDLE değerleri işletim sistemi düzeyinde 
	elde edilmiş durumdadır. Ancak burada bu handle değerleri POSIX sistemlerindeki gibi baştan belli değildir. GetStdHandle API fonksiyonuyla bunlar
	elde edilmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hStdin, hStdout;
	char buf[4096];
	DWORD dwRead, dwWritten;

	if ((hStdin = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	if (!ReadFile(hStdin, buf, 4096, &dwRead, NULL))
		ExitSys("ReadFile");

	if (!WriteFile(hStdout, buf, dwRead, &dwWritten, NULL))
		ExitSys("WriteFile");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	C'nin Stdio ktüphenesinin yazımı için bir ipucu (tam bitilmiş bir kod değil)
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* csd_stdio.h */

#ifndef CSD_STDIO_H_
#define CSD_STDIO_H_

#define CSD_EOF         -1
#define CSD_BUFSIZ      5

#include <sys/types.h>

typedef struct {
	int fd;
	unsigned char *beg;    /* starting buffer address */
	size_t size;   		  /* buffer size */
	size_t count; 		  /* number of bytes in the buffer */
	unsigned char *pos;    /* current buffer address */
	off_t offset;  		  /* file offset */
	int dirty;
	int error;
	int eof;
	/* .... */
} CSD_FILE;

CSD_FILE *csd_fopen(const char *path, const char *mode);
int csd_fgetc(CSD_FILE *f);

#endif

/* csd_stdio.c */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "csd_stdio.h"

static ssize_t refresh_buffer(CSD_FILE *f);

CSD_FILE *csd_fopen(const char *path, const char *mode)
{
	CSD_FILE *f;
	int i;
	static char *modes[] = { "r", "r+", "w", "w+", "a", "a+", "rb", "r+b", "wb", "w+b", "ab", "a+b", NULL };
	static int flags[] = { O_RDONLY, O_RDWR, O_WRONLY | O_CREAT | O_TRUNC, O_RDWR | O_CREAT | O_TRUNC, O_WRONLY | O_CREAT | O_APPEND,
		O_WRONLY | O_CREAT | O_APPEND, O_WRONLY | O_CREAT | O_APPEND };

	if ((f = (CSD_FILE *)malloc(sizeof(CSD_FILE))) == NULL)
		return NULL;

	for (i = 0; modes[i] != NULL; ++i)
		if (!strcmp(mode, modes[i]))
			break;

	if (modes[i] == NULL) {
		free(f);
		return NULL;
	}

	if ((f->fd = open(path, flags[i % 6], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		free(f);
		return NULL;
	}

	if ((f->beg = (unsigned char *)malloc(CSD_BUFSIZ)) == NULL) {
		free(f);
		return NULL;
	}

	f->size = CSD_BUFSIZ;
	f->count = 0;
	f->pos = NULL;
	f->offset = 0;
	f->dirty = 0;
	f->error = 0;

	return f;
}

static ssize_t refresh_buffer(CSD_FILE *f)
{
	ssize_t result;

	if (f->dirty) {
		if (lseek(f->fd, f->offset, SEEK_SET) == -1)
			return -1;
		if (write(f->fd, f->beg, f->pos - f->beg) == -1)
			return -1;
	}

	if (lseek(f->fd, f->offset + f->count, SEEK_SET) == -1)
		return -1;

	if ((result = read(f->fd, f->beg, f->size)) == -1)
		return -1;

	f->pos = f->beg;
	f->offset = f->offset + f->count;
	f->count = result;

	return result;
}

int csd_fgetc(CSD_FILE *f)
{
	ssize_t result;

	if (f->pos == NULL || f->pos == f->beg + f->count) {
		if ((result = refresh_buffer(f)) == -1) {
			f->error = 1;
			return CSD_EOF;
		}

		if (result == 0) {
			f->eof = 1;
			return CSD_EOF;
		}
	}

	return *f->pos++;
}

int csd_ferror(CSD_FILE *f)
{
	return f->error;
}

/* sample.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "csd_stdio.h"

void exit_sys(const char *msg);

int main(void)
{
	CSD_FILE *f;
	int ch;

	if ((f = csd_fopen("test.txt", "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	ch = csd_fgetc(f);
	putchar(ch);

	while ((ch = csd_fgetc(f)) != CSD_EOF)
		putchar(ch);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	freopen standart C fonksiyonu stdin, stdout ve stderr dosyalarını (ve diğer dosyaları da) yönlendirmek için kullanılabilmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *f;
	int i;

	if ((f = freopen("test.txt", "w", stdout)) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; ++i)
		printf("%d\n", i);

	fclose(f);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	freopen ile stdin dosyasının yönlendirilmesi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *f;
	int i;
	int val;

	if ((f = freopen("test.txt", "r", stdin)) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while (scanf("%d", &val) == 1)
		printf("%d\n", val);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerindeki C derleyicilerinde stdout dosyası default durumda satır tamponlamalı moddadır. Halbuki Windows sistemlerindeki C derleyici
	lerinde sıfır tamponlamalı moddadır. Bu nedenle aşağıdaki programda "ankara" yazısı UNIX/Linux sistemlerinde görülmeyecek ancak Windows sistemlerinde
	görülecektir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	printf("ankara");

	for (;;)
		;
	
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tabii biz fflush fonksiyonuyla stdout dosyasını tazaleyebiliriz. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	printf("ankara");
	fflush(stdout);

	for (;;)
		;
		
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	En kötü olasılıkla stdout satır tamponlamalı olacağına göre aşağıdaki kodda her zaman "ankara" yazısı ekranda görüntülecenektir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	printf("ankara\n");

	for (;;)
		;
		
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	stdin dosyası işletim sistemlerinden dolayı genellikle default durumda ya da sonradan sıfır tamponlamalı moda sokulamamaktadır. Bu nedenle
	Windows sistemlerinde ve UNIX/Linux sistemlerinde stdin satır tamponlamalıdır. Yani bir stdin dosyasından bir karaleter bile okumak istesek
	eğer tampon doluysa bize bu karakter tampon verilir. Eğer tampon boş ise bizden bir satırlık bilgi istenir. Tampondaki satırın 
	sonunda '\n' karakteri de bulnmaktadır. Dolsyısıyla aşağıdaki kodda ikinci getchar klavyeden giriş beklemez. Tampondaki '\n' karakterini alarak 
	geri döner. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int ch;
	
	ch = getchar();
	printf("%c (%d)", ch, ch);

	ch = getchar();
	printf("%c (%d)", ch, ch);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	stdin tamponunu başaltabilen standart bir fonksiyon yoktur. Dolayısıyla programcının bunu bir fonksiyon ya da makroyla yapması gerekir. 
	Aşağıda böyle bir fonksiyon görülmektedir. Fonksiyondaki EOF konntrolü program bazı uç durumlarda gerekebilmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void clear_stdin(void)
{
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}

int main(void)
{
	int ch;

	ch = getchar();
	printf("%c\n", ch);
	
	clear_stdin();
	
	ch = getchar();
	printf("%c\n", ch);
	
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Yukarıdaki clear_stdin bir makro olarak da yazılabilirdi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#define clear_stdin()			\
do {							\
		int ch;					\
								\
	} while ((ch = getchar()) != '\n' && ch != EOF)	

int main(void)
{
	int ch;

	ch = getchar();
	printf("%c\n", ch);
	
	clear_stdin();
	
	ch = getchar();
	printf("%c\n", ch);
	
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	İstersek işin başında stdout dosyasının da default tapmonlama modunu setbuf ya da setvbuf fonksiyonlarıyla değiştirebiliriz. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	printf("ali");

	for (;;)
		;

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	gets fonksiyonun gerçekleştirimi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

char *mygets(char *str)
{
	int ch;
	size_t i;

	for (i = 0; (ch = getchar()) != '\n' && ch != EOF; ++i)
		str[i] = ch;

	if (i == 0 && ch == EOF)
		return NULL;

	str[i] = '\0';

	return str;
}

int main(void)
{
	char s[100];
	
	mygets(s);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	C11'de gets fonksiyonu kaldırılmış ve yerine isteğe bağlı biimde gets_s fonksiyonu eklenmiştir. gets_s Microsoft derleyicilerinde zaten uzun süredir
	bulunmaktadır. Ancak gcc ve clang'ın kullandığı glibc kütüphanesinde bu fonksiyon bulunmamaktadır. Aşağıda bu fonksiyonun gerçekleştirimi yapılmıştır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

char *mygets_s(char *str, size_t size)
{
	size_t i;
	int ch;

	for (i = 0; i < size - 1; ++i) {
		if ((ch = getchar()) == '\n' || ch == EOF)
			break;
		str[i] = ch;
	}

	if (i == 0 && ch == EOF)
		return NULL;

	str[i] = '\0';

	return str;
}

int main(void)
{
	char s[10];
	
	mygets_s(s, 10);
	puts(s);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	gets_s yeri,ne fgets fonksiyonu aşağıdaki gibi kullanılabilir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[10];
    char *str;

    if ((str = fgets(s, 10, stdin)) != NULL)
        if ((str = strchr(s, '\n')) != NULL)    
            *str = '\0';

    if (str != NULL)        
        puts(s);

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Önce getchar, sonra gets kullanırken stdin tamponun boşaltılması gerekebilir
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void empty_stdin(void)
{
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}

int main(void)
{
	int ch;
	char name[512];

	printf("Bir karakter giriniz:");
	fflush(stdout);

	ch = getchar();
	empty_stdin();

	printf("Bir isim giriniz:");
	fflush(stdout);

	gets(name);

	printf("'%c' - \"%s\"\n", ch, name);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tabii önce gets sonra getchar kullanılıyor olsaydı tamponu boşaltmaya gerek kalmazdı
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int ch;
	char name[512];

	printf("Bir isim giriniz:");
	fflush(stdout);
	gets(name);

	printf("Bir karakter giriniz:");
	fflush(stdout);
	ch = getchar();

	printf("'%c' - \"%s\"\n", ch, name);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	scanf fonksiyonu ile menü oluştururken geçirsiz girişlerin ele alınması örneği
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void empty_stdin(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int disp_menu(void)
{
	int option;

	printf("1) Ara\n");
	printf("2) Sil\n");
	printf("3) Çıkış\n\n");
	
	printf("Seçiminiz:");

	if (scanf("%d", &option) == 0) {
		empty_stdin();
		return 0;
	}

	return option;
}

int main(void)
{
	int option;

	for (;;) {
		option = disp_menu();

		switch (option) {
			case 1:
				printf("Aranıyor\n\n");
				break;
			case 2:
				printf("Siliniyor\n\n");
				break;
			case 3:
				goto EXIT;
			default:
				printf("Geçersiz giriş!\n\n");
		}
	}
EXIT:
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	scanf fonksiyonunda format karakterleri arasındaki karakterlerin girişlerde mutlaka bulundurulması gerekir. Format karakterlerindeki herhangi bir 
	boşluk karakteri "boşluk karakteri görmeyene kadar stdin'den okuma yap ve onları at" anlamına gelmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int day, month, year;

	printf("Tarihi dd/mm/yy biçiminde giriniz:");
	scanf("%d/%d/%d", &day, &month, &year);

	printf("%d-%d-%d\n", day, month, year);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	scanf fonksiyonunun baştaki boşluk karakterlerini (leading space) attığına, ancak sondakileri (trailing space) atmadığına dikkat edniz. 
	Bu durumda scanf fonksiyonundan sonra gets, getchar gibi fonksiyonları kullanmadan önce stdin tamponun boşaltılması gerekebilir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

void empty_stdin(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int main(void)
{
	int no;
	char name[120];

	printf("No:");
	scanf("%d", &no);

	empty_stdin();	

	printf("Adı soyadı:");
	gets(name);

	printf("No: %d, Name: %s\n", no, name);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	EOF görene kadar scanf ile okuma yapan bir örnek
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void)
{
	int val;

	while (scanf("%d", &val) != EOF) 
		printf("%d\n", val);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	getenv standart C fonksiyonu ile bir çevre değişkeninin değerinin elde eidlmesi
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *val;

	if ((val = getenv("PATH")) == NULL) {
		fprintf(stderr, "Environment variable not found!..\n");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", val);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde çevre değişkenini elde eden asıl fonksiyon GetEnvironmentVariable isimli API fonksiyonudur. Aslında
	getenv bu sistemlerde bu API fonksiyonunu çağırmaktadır. UNIX/Linux sistemlerinde ise gerçekten asıl fonksiyon getenv fonksiyonudur.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define SIZE	4096

int main(void)
{
	char val[SIZE];
	DWORD dwResult;

	if ((dwResult = GetEnvironmentVariable("PATH", val, SIZE)) == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND) {
		fprintf(stderr, "Environment variable not found!..\n");
		exit(EXIT_FAILURE);
	}

	if (dwResult > SIZE) {
		fprintf(stderr, "Insufficient buffer!..\n");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", val);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde setenv fonksiyonu ile prosesin çevre değişkeni değiştirilebilir, ekleme yapılabilir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void exit_sys(const char *msg);

int main(void)
{
	char *env;

	if (setenv("CITY", "Ankara", 1) == -1)
		exit_sys("setenv");

	if ((env = getenv("CITY")) == NULL) {
		fprintf(stderr, "cannot get environment variable!..\n");
		exit(EXIT_FAILURE);
	}
	puts(env);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX(Linux sistemlerinde puenv isimli bir POSIX fonksiyonu da vardır. Bu fonksiyon Windows sistemlerinde _putenv ismiyle de bulunmaktadır. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void exit_sys(const char *msg);

int main(void)
{
	char *env;

	if (putenv("CITY=Ankara") == -1)
		exit_sys("putenv");

	if ((env = getenv("CITY")) == NULL) {
		fprintf(stderr, "cannot get environment variable!..\n");
		exit(EXIT_FAILURE);
	}
	puts(env);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde çevre değişkenini set eden asıl fonksiyon SetEnvironmentVariable isimli API fonksiyonudurç
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define SIZE	4096

int main(void)
{
	char val[SIZE];
	DWORD dwResult;

	if (!SetEnvironmentVariable("CITY", "Ankara")) {
		fprintf(stderr, "Cannot set environment variable!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dwResult = GetEnvironmentVariable("CITY", val, SIZE)) == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND) {
		fprintf(stderr, "Environment variable not found!..\n");
		exit(EXIT_FAILURE);
	}

	if (dwResult > SIZE) {
		fprintf(stderr, "Insufficient buffer!..\n");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", val);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	UNIX/Linux sistemlerinde prosesin tüm çevre değişkenlerini elde edebilmek için environ isimli global göstericiyi gösteren göstericiden 
	faydalanılmaktadır. Bu göstericinin maalesef extern bildirimi herhangi bir başlık dosyasında yoktur.
-------------------------------------------------------------------------------------------------------------------------------------------*/

int main(void)
{
	int i;

	for (i = 0; environ[i] != NULL; ++i)
		puts(environ[i]);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde GetEnvironmentStrings isimli API fonksiyonu çevre değişken listesini tek bir adresle 
	Anahtar=Değer\0Anahtar=Değer\0Anahtar=Değer\0\0
	biçiminde vermektedir. Söz konusu çevre değişken bloğu istenirse FreeEnvironmentStrings API fonksiyonuyla boşaltılabilir.
	(Yani bu fonksiyon çağrıldıktan sonra artık proseste çevre değişkeni kalmaz.)
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(void)
{
	LPCH envStr;

	if ((envStr = GetEnvironmentStrings()) == NULL) {
		fprintf(stderr, "Cannot get environment strings!..\n");
		exit(EXIT_FAILURE);
	}

	while (*envStr != '\0') {
		puts(envStr);
		envStr += strlen(envStr) + 1;
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Çevre değişkenleri sayesinde programlar kullanıcı tarafından ayarlanabilen çeşitli belirlemeleri kullanabilir. Aşağıdaki örnekte program
	"x.dat" isimli bir dosyayı DATADIR isimli bir çevre değişkeninin bulunduğu yerde aramamaktadır. Eğer bu çevre değişkeni yoksa dosya 
	prosesin çalışma dizininde arayacaktır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define DATAFILE		"x.dat"

int main(void)
{
	char *val;
	char path[4096];
	FILE *f;

	if ((val = getenv("DATADIR")) != NULL)
		sprintf(path, "%s/%s", val, DATAFILE);
	else
		sprintf(path, "./%s", DATAFILE);

	if ((f = fopen(path, "rb")) == NULL) {
		fprintf(stderr, "cannot open data file!..\n");
		exit(EXIT_FAILURE);
	}
	printf("Ok\n");

	/* ... */

	fclose(f);

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde proses yaratmak için (yani bir programı çalıştırabilmek için) CreateProcess isimli API fonksiyonu kullanılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

/* Prog1.c */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char szPath[] = "Prog2 ali veli selami";
	char env[] = "ALI=10\0Veli=20\0";
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pa;

	if (!CreateProcess(NULL, szPath, NULL, NULL, TRUE, 0, env, "c:\\windows", &si, &pa))
		ExitSys("CreateProcess");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/* Prog2.c */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(int argc, char *argv[])
{
	LPCH envStr;
	char cwd[MAX_PATH];
	int i;

	printf("Command line arguments:\n");

	for (i = 0; i < argc; ++i)
		puts(argv[i]);

	printf("Current Woring Directory:\n");

	GetCurrentDirectory(MAX_PATH, cwd);
	printf("%s\n", cwd);

	printf("Environment Variables:\n");

	if ((envStr = GetEnvironmentStrings()) == NULL) {
		fprintf(stderr, "Cannot get environment strings!..\n");
		exit(EXIT_FAILURE);
	}

	while (*envStr != '\0') {
		puts(envStr);
		envStr += strlen(envStr) + 1;
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	CreateProcess fonksiyonun birinci parametresi NULL geçilirse ikinci parametre boşluk karakterleriyle parse edildiğinden zaten boşluk karakteri içeren 
	dizinlerde sorun ortaya çıkar. Bu nedenle böylesi durumlarda ikinci parametredeki yazının tırnaklanması gerekmektedir. 
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char szPath[] = "\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\" csystem.org cumhuriyet.com\"";
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pa;

	if (!CreateProcess(NULL, szPath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pa))
		ExitSys("CreateProcess");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Tabii birinci parametre NULL geçilmedikten sonra bu tırnaklamanın birinci parametre için yapılmasına gerek yoktur
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char szPath[] = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\" csystem.org cumhuriyet.com";
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pa;

	if (!CreateProcess("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe", szPath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pa))
		ExitSys("CreateProcess");

	printf("Ok\n");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	Windows sistemlerinde HANDLE türüyle belirtilen tüm nesnelere (dosyalara, thread'lere, proseslere vs.) "kernel nesneleri" denilmektedir. 
	Tüm kernel nesneleri prosese özgü "proses handle tablosu" denilen bir tabloda giriş belirtmektedir. Tüm kernel nesnelerinin yok edilmesi (ya da
	kapatılması) CloseHandle isimli API fonksiyonu ile yapılmaktadır.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char szPath[] = "notepad.exe";
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pa;

	if (!CreateProcess(NULL, szPath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pa))
		ExitSys("CreateProcess");

	CloseHandle(pa.hProcess);
	CloseHandle(pa.hThread);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------
	ShellExecute fonksiyonu katman olarak bir shell fonksiyonudur. Dolayısıyla aslında kendi içerisinde CreateProcess fonksiyonunu çağırmaktadır.
	ShellExecute exeutable olmayan bir dosyayı da parametre olarak alabilir. Onun ilişkili olduğu executable dosyayı CreateProcess ile çalıştırıp
	söz konusu dosyayı da ona komut satırı argümanı olarak vermektedir.
-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HINSTANCE hInstance;

	hInstance = ShellExecute(NULL, "open", "C:\\Users\\CSD\\Desktop\\playlist.csv", NULL, NULL, SW_NORMAL);
	if ((int)hInstance < 32)
		ExitSys("ShellExecute");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------------------*/

