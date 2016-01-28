import subprocess, datetime, os

def checkWiki():
	if not os.path.isdir(".git"):
		print "this doesn't seem to be a git repo"
		return None
	url = subprocess.check_output(["git", "config", "--get", "remote.origin.url"])
	if url.find('.git') == -1:
		repo = url[url.rindex('/')+1:-1]
	else:
		repo = url[url.rindex('/')+1:url.rindex('.git')]
	wikiRepo = repo+'.wiki'
	if not os.path.isdir(wikiRepo):
		print 'wiki repo not found, git cloning ' + wikiRepo
		wikiUrl = url[:url.rindex('/')+1]+wikiRepo+'.git'
		subprocess.call(["git","clone",wikiUrl])
	else:
		print "pulling latest wiki"
		subprocess.call("( cd "+wikiRepo+" && git pull )",shell=True)
	return wikiRepo

def getUsername():
	username = subprocess.check_output(["git", "config", "user.name"])
	name = username.partition(" ")[0]
	return name

def getFile(username,wikiRepo):
	fileName = wikiRepo+'/'+username+"'s-todos.md"

	try:
		with open(fileName,'r') as f:
			f.close()
	except:
		subprocess.call(["touch",fileName])
		print 'todo not found, creating now'
		with open(fileName,'w') as f:
			tableHeader = 'Date | Todo\n:---: | :---'
			f.write(tableHeader)
			f.close()
	return fileName

def composeTodos(fileName,todos):
	push = '\n'
	d = datetime.date.today()
	push += d.isoformat()+ ' | <ul>'
	for t in todos:
		push += '<li>'+t+'</li>'
	push += '</ul>'
	with open(fileName,'a') as f:
		f.write(push)
		f.close()

def inputTodos():
	todos = []
	done = False
	t = raw_input('Enter your todos:\n')
	while t != '':
		todos.append(t)
		t = raw_input('')
	return todos

def pushWikiChanges(wikiRepo,fileName):
	addName = fileName[fileName.rindex('/')+1:].replace(" ","\ ")
	addName = addName.replace("'","\\'")
	subprocess.call("( cd "+wikiRepo+" && git add "+addName+" )", shell = True)
	subprocess.call("( cd "+wikiRepo+" && git commit -m 'added todos' )", shell = True)
	subprocess.call("( cd "+wikiRepo+" && git push origin master )", shell = True)

def main():
	wikiRepo = checkWiki()
	if wikiRepo == None:
		return
	username = getUsername()
	fileName = getFile(username,wikiRepo)
	todos = inputTodos()
	if todos != []:
		composeTodos(fileName,todos)
		pushWikiChanges(wikiRepo,fileName)

main()