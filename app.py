import requests
from bs4 import BeautifulSoup
import csv
from concurrent.futures import ThreadPoolExecutor
# import sysimport os
#from googletrans import Translator
import subprocess
#from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
#db = SQL("sqlite:///es.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
# GETはアクセスしたとき、POSTはデータを追加するとき
def index():
    '''result ='0'
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        f = open('ex.txt', 'w')
        f.write(name)
        f.close()
        result = subprocess.run(["./speller", "ex.txt"])
        print(result)
        # month=request.form.get("month")
        # day=request.form.get("day")

        #db.execute("INSERT INTO birthdays (name,month,day) VALUES(?,?,?)",name,month,day)

        #return redirect("/")
        return render_template("index.html")


    else:'''

    # TODO: Display the entries in the database on index.html

    # return render_template("index.html",birthdays=db.execute("SELECT * FROM birthdays"))
    return render_template("index.html")


@app.route("/grade", methods=["GET", "POST"])
# GETはアクセスしたとき、POSTはデータを追加するとき
def grade_f():
    result = '0'
    # if request.method == "POST":

    # ユーザーの入力した英文をex.txtに入力
    name = request.form.get("name")
    f = open('ex.txt', 'w')
    f.write(name)
    f.close()

    # 入力した英文を単語ごとに改行
    subprocess.run(["./7-2", "ex.txt", "ex2.txt"])

    # 単語を原形に変換
    f = open('ex2.txt', 'r')
    datalist = f.readlines()
    f.close()
    #f1 = open('ex3.txt', 'w')
    i = 0
    urls = []

    for data in datalist:
        # print(i)
        # print("---"+data[:-1]+'---')
        #i += 1
        search_word = "https://ejje.weblio.jp/content/" + data[:-1]
        #url = requests.get(search_word)
        urls.append(search_word)
        """soup = BeautifulSoup(url.text, "html.parser")
        try:
            word_form = soup.find(class_='lemmaAnc').get_text()

        except:
            word_form = data[:-1]

        # print(word_form)

        f1.write(word_form)
        f1.write("\n")
        """

    # f1.close()
    f1 = open('ex3.txt', 'w')

    # print(urls)
    with ThreadPoolExecutor(max_workers=8) as executor:
        results = list(executor.map(requests.get, urls))
        """for index in range(len(results)):
            soup = BeautifulSoup(results[index].text, "html.parser")
            print(results[index].text)
            try:
                word_form = soup.find(class_='lemmaAnc').get_text()

            except:
                word_form = data[:-1]

            #print(word_form)

            f1.write(word_form)
            f1.write("\n")"""



    for index in range(len(results)):
        soup = BeautifulSoup(results[index].text, "html.parser")
        try:
            word_form = soup.find(class_='lemmaAnc').get_text()

        except:
            word_form = datalist[index][:-1]

        # print(word_form)

        f1.write(word_form)
        f1.write("\n")

    f1.close()

    # 単語の処理をし終わったファイルを用いて習っていない単語、%をstudent.txtに出力
    subprocess.run(["./speller", "ex3.txt", ">", "student.txt"])

    # student.txtの内容をユーザーに出力

    # print(result)
    responce = [
        [""],
        [""],
        [""],
        [""],
        [""],
        [""]
    ]
    word_mean = []
    misses = ["miss/0", "miss/1", "miss/2", "miss/3", "miss/4", "miss/5"]
    zz = 0


    for miss in misses:
        f = open(miss, 'r')
        result = f.readlines()
        # print(result)
        f.close()
        for res in result:
            responce[zz].append(res[:-1])
            # print(responce[zz])
        zz += 1


        """search_word = "https://ejje.weblio.jp/content/" + res[:-1]
        url = requests.get(search_word)
        soup = BeautifulSoup(url.text, "html.parser")
        try:
            word_mean.append(soup.find(class_='content-explanation ej').get_text())

        except:
            word_mean.append("This word doesn't exist.")

    #print(word_mean)"""

    f = open('student3.txt', 'r')
    percent = f.readlines()
    # print(result)
    f.close()


    return render_template("grade.html", result=responce, percent=percent,word_mean=word_mean)

"""source"""

'''result = subprocess.run(["./word4", "./input1_lf.txt" ,"./texts/out.txt"])
#print(result)

with open('./texts/out.txt') as f:
    lines = f.readlines()
    #f.close()



with open('trans.txt', 'w', encoding='UTF-8') as f:

    translator = Translator()
    for line in lines:
        translated = translator.translate(line, dest="ja")
        f.write(line)  # 翻訳したい文章
        #f.write("   ")
        f.write(translated.text)  # 翻訳後の文章
        f.write("\n")
    #f.close()
    '''
