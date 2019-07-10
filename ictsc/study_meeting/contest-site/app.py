from flask import Flask,render_template
import markdown

app = Flask(__name__)
md = markdown.Markdown(extensions=['tables'])

@app.route('/')
def index():
    open_file = open("static/index.md","r")
    text = open_file.read()
    result = render_template('index.html',text=md.convert(text))
    open_file.close()
    return result

@app.route('/problem')
def problem():
    open_file = open("static/problem.md","r")
    content = open_file.read()
    result = render_template('problem.html',content=md.convert(content))
    open_file.close()
    return result

@app.route('/problem/<problem_name>',methods=["GET"])
def problem_name(problem_name):
    if problem_name == "Infrastructure" :
        return render_template('Infrastructure.html')
    try:
        open_file = open("static/" + problem_name + ".md","r")
        content = open_file.read()
        result = render_template('problem.html',content=md.convert(content),problem=problem_name)
        open_file.close()
        return result
    except IOError:
        open_file = open("static/404.md","r")
        content = open_file.read()
        result = render_template('index.html',text=md.convert(content))
        open_file.close()
        return result

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=80,threaded=True)