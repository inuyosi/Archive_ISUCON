from flask import Flask,render_template,request
import markdown
import copy
import re
from pathlib import Path
import os

app = Flask(__name__)
md = markdown.Markdown(extensions=['tables'])
name_list =["all_team"]
ip_address = "150.89.233.27" #任意のIPアドレスに変更
problem_flag = False
answer_flag = False

post_data = {}
post_data["default"] = {"team-name":'null',"comment":'null',"parsentage":0}

@app.route('/')
def index():
    open_file = open("static/index.md","r")
    text = open_file.read()
    result = render_template('index.html',text=md.convert(text))
    open_file.close()
    return result

@app.route('/problem')
def problem():
    problem_parsentage = '## 問題正答/解答状況\n'
    content ="## 問題一覧\n"
    for name in name_list :
        path = Path("static/problem/" + name)
        content += "####" + name + " 解答問題\n"
        for i in list(path.glob("*.md")) :
            if problem_flag :
                data = str(i).replace("static/","").replace(".md","")
                print (data)
                content += ("- ["+ data.replace("problem/"+ name +"/","") + \
                           "](http://" + ip_address +"/"+ data +")\n" )
    
    for key in post_data :
        if not key == 'default' :
            problem_parsentage += "- [" + key + "](http://"+ ip_address +"/problem/" + \
                                key +"/check) " + str(post_data[key]["parsentage"]) + \
                                 "% / 100%\n"
    result = render_template('problem.html',content=md.convert(content),\
             problem_parsentage=md.convert(problem_parsentage))
    return result

@app.route('/answer')
def answer():
    path = Path("static/answer/")
    content = "## 解説一覧\n"
    if answer_flag :
        for i in list(path.glob("*.pdf")) :
            if problem_flag :
                data = str(i)
                content += ("- ["+ data.replace("static/answer/","").replace(".pdf","") + \
                           "](http://"+ ip_address +"/"+ data +")\n" )
    result = render_template('index.html',text=md.convert(content))
    return result

@app.route('/problem/<team_name>/<problem_name>',methods=["GET"])
def problem_name(team_name,problem_name):
    if not problem_name == "Infrastructure" :
        try:
            open_file = open("static/problem/" + team_name + "/"+ problem_name + ".md","r")
            content = open_file.read()
            if team_name == "all_team" :
                result = render_template('anyteam-problem.html',content=md.convert(content),\
                         problem=problem_name)
            else :
                result = render_template('problem.html',content=md.convert(content),\
                         problem=problem_name)   
            open_file.close()
        except IOError:
            open_file = open("static/404.md","r")
            content = open_file.read()
            result = render_template('index.html',text=md.convert(content))
            open_file.close()
    else :
        result = render_template("Infrastructure.html")
    return result

@app.route('/problem/<team_name>/<problem_name>',methods=["POST"])
def problem_post(team_name,problem_name):
    if problem_name == "Infrastructure" :
        res3  = ""
        for i in range(20) :
            number = i + 2
            res3 += request.form['test'+str(number)] 
    else :
        res3 = request.form['test3']
    if team_name == "all_team" :
        res1 = request.form['test1']
        post_name = problem_name +"_" + res1
    else :
        res1 = team_name
        post_name = problem_name
    if not post_name in post_data : 
        post_data[post_name] = copy.deepcopy(post_data["default"])
    post_data[post_name]['team-name'] = res1
    post_data[post_name]['comment'] = str(res3.replace('\r',''))
    try:
        open_file = open("static/problem/"+ team_name + "/" + problem_name + ".md","r")
        result = render_template('index.html',text="Send OK")
        open_file.close()
    except IOError:
        result = render_template('index.html',text="NOT file")
    return result

@app.route('/problem/<problem_name>/check',methods=["GET"])
def problem_check(problem_name):
    if problem_name in post_data :
        result = render_template('check.html',team_name=str(post_data[problem_name]['team-name']),comment=md.convert(str(post_data[problem_name]['comment'])).replace('\n','<br>'))
    else :
        open_file = open("static/404.md","r")
        result = render_template('index.html',text=md.convert(open_file.read()))
        open_file.close()
    return result

@app.route('/problem/<problem_name>/check',methods=["POST"])
def parsentage_post(problem_name):
    res1 = request.form['test1']
    post_data[problem_name]['parsentage'] = res1
    result = render_template('index.html',text="Send OK")
    return result

@app.route('/change',methods=["GET"])
def change_flag():
    global answer_flag
    global problem_flag
    if not problem_flag :
        problem_flag = True
    elif answer_flag :
        answer_flag = problem_flag = False
    else :
        answer_flag = True
    return "OK"

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=80,threaded=True)