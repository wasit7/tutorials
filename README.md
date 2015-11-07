# tutorials
This tutorials for computer programming 

To update .gitignore
.gitignore will only effect files that haven't been 'added' already.

To make new .gitignore entries affect all files

Make changes to .gitignore
git commit -a -m "Pre .gitignore changes"
git rm -r --cached .
git add .
git commit -a -m "Post .gitignore changes"
git status should output "nothing to commit (working directory clean)"