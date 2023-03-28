/*
* クラス:A
* 学籍番号:210441058
* 氏名:清水陽生
*/
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#define LEN 1024

void error(void) {//標準エラー出力の関数化
	printf("usage: test6-3 [options...] <input file> <output file>\noptions:\n    -p       : enable pass - through mode\n    -h       : display this message\n");
}
char small(char a) {//入力引数の文字列を小文字に変換する関数．
	int i = 0;
	if ('A' <= a && a <= 'Z') {
		a = a - 'A' + 'a';//文字列がアルファベットのとき小文字に変換する
	}
	return a;
}
int alpha(char* buf) {
	int i = 0;
	while (buf[i] != '\0') {
		if (('a' <= buf[i] && buf[i] <= 'z') || ('A' <= buf[i] && buf[i] <= 'Z')) {
			return 0;//文字列の中にアルファベットが一つでもあったとき、0を返す
		}
		i++;
	}

	return 1;//文字列の中にアルファベットが一つもなかった時
}
//int argc, char* argv[]
int main(int argc, char* argv[]) {//コマンドライン引数から2つのファイル名を取得//int argc, char* argv[]
	FILE* in = NULL;
	FILE* out = NULL;

	char buf[LEN]; /* fgets() 用バッファは十分なサイズのものを用意 */
	char buf2[LEN];//出力用に別途用意
	int c;
	int m;
	int k = 0;
	int i = 0;
	int p = 0;

	for (m = 0; m < LEN; m++) {
		buf[m] = '\0';//bufを初期化
		buf2[m] = '\0';//buf2を初期化
	}
	if (argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'p': /* オプション -p が指定された */
			in = fopen(argv[2], "r");//ファイル名を指定して1つ目のファイルは読み専用で開き，2つ目のファイルは書き専用で開く
			out = fopen(argv[3], "w");
			while (fgets(buf, sizeof(buf), in) != NULL) {
				fputs(buf, out);//1つ目のファイルの内容を fgets で繰り返し読み込み，2つ目のファイルに書き込み
			}
			fclose(in);//ファイルを閉じる
			fclose(out);
			break;
		case 'h': /* オプション -b が指定された*/
			error();
			return EXIT_FAILURE;
			break;
		}
	}
	else {
		if (argc != 3) { /* コマンドライン引数の数が想定していたものと違えばエラー */
			error();
			return EXIT_FAILURE;
		}
		in = fopen(argv[1], "r");//ファイル名を指定して1つ目のファイルは読み専用で開き，2つ目のファイルは書き専用で開く
		out = fopen(argv[2], "w");
		while ((c = fgetc(in)) != EOF)//1つ目のファイルの内容を fgetc で繰り返し読み込み，2つ目のファイルに書き込み
		{
			if (c == '\\') {
				fputs("\n", out);//改行文字を出力
				continue;//cが改行文字であるときスキップ
			}
			if (isspace(c))  // cが空白文字の場合
			{
				k = 0;
				i = 0;
				p = 0;

				if (alpha(buf) == 0) {//アルファベットを含む行だけのとき
					while (buf[i] != '\0') {
						if (('a' <= buf[i] && buf[i] <= 'z') || ('A' <= buf[i] && buf[i] <= 'Z') || (buf[i] == '-')) {

							buf2[p] = buf[i];//アルファベットか-の時buf2に格納
							p++;
						}
						else if (buf[i] == '\'') {
							if (buf[i + 1] == 's') {
								i++;//-があり後にsも出てくるとき、'sを削除するためにiを一つ余分にインクリメント
							}
							else {//-があり後にsが出てこないときbuf2に格納
								buf2[p] = buf[i];
								p++;
							}
						}
						i++;
					}

					fputs(buf2, out);//bufに保存した文字列をファイル出力
					fputs("\n", out);//改行文字を出力
				}
				for (m = 0; m < LEN; m++) {
					buf[m] = '\0';//bufを初期化
					buf2[m] = '\0';//buf2を初期化
				}
			}
			else {
				buf[k] = small(c);//アルファベットは小文字に変換してbufに保存
				k++;
			}
		}
		fclose(in);// ファイルを閉じる
		fclose(out);
	}
	return EXIT_SUCCESS;
}
