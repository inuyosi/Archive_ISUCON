from flask import Flask,render_template,request
import markdown
import copy
import re

app = Flask(__name__)
md = markdown.Markdown(extensions=['tables'])

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
    open_file = open("static/problem.md","r")
    content = open_file.read()
    for key in post_data :
        if not key == 'default' :
            problem_parsentage += "- [" + key + "](http://150.89.233.27/problem/" + \
                                key +"/check) " + str(post_data[key]["parsentage"]) + \
                                 "% / 100%\n"
    result = render_template('problem.html',content=md.convert(content),problem_parsentage=md.convert(problem_parsentage))
    open_file.close()
    return result

@app.route('/problem/<problem_name>',methods=["GET"])
def problem_name(problem_name):
#    if problem_name == "Infrastructure" :
#        result = render_template('Infrastructure.html')
#    else: 
        try:
            open_file = open("static/" + problem_name + ".md","r")
            content = open_file.read()
            result = render_template('problem.html',content=md.convert(content),problem=problem_name)
            open_file.close()
        except IOError:
            open_file = open("static/404.md","r")
            content = open_file.read()
            result = render_template('index.html',text=md.convert(content))
            open_file.close()
#   return result
        return result

@app.route('/problem/<problem_name>',methods=["POST"])
def problem_post(problem_name):
    res1 = request.form['test1']
    res3 = request.form['test3']
    if not problem_name in post_data : 
        post_data[problem_name] = copy.deepcopy(post_data["default"])
    post_data[problem_name]['team-name'] = res1
    post_data[problem_name]['comment'] = str(res3.replace('\r',''))
    print (res3.replace('\r',''))
    try:
        open_file = open("static/"+ problem_name + ".md","r")
        result = render_template('index.html',text="Send OK")
        open_file.close()
    except IOError:
        result = render_template('index.html',text="NOT file")
    return result

@app.route('/problem/<problem_name>/check',methods=["GET"])
def problem_check(problem_name):
    try:
        open_file = open("static/" + problem_name + ".md","r")
        open_file.close()
        if not problem_name in post_data : 
            post_data[problem_name] = copy.deepcopy(post_data["default"])
        result = render_template('check.html',\
                 team_name=str(post_data[problem_name]['team-name']),\
                 comment=md.convert(str(post_data[problem_name]['comment'])).replace('\n','<br>'))
    except IOError:
        open_file = open("static/404.md","r")
        content = open_file.read()
        result = render_template('index.html',text=md.convert(content))
        open_file.close()
    return result

@app.route('/problem/<problem_name>/check',methods=["POST"])
def parsentage_post(problem_name):
    res1 = request.form['test1']
    post_data[problem_name]['parsentage'] = res1
    try:
        open_file = open("static/"+ problem_name + ".md","r")
        result = render_template('index.html',text="Send OK")
        open_file.close()
    except IOError:
        result = render_template('index.html',text="NOT file")
    return result

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=80,threaded=True)