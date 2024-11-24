## Assignment 3: ADTs: Symbol Table

IOANNIS CHATZIANTONIOU CSD5193

## Make Repository Private and Add TAs as Members
You can make the repo private and add TAs as members by hand or using
the private.py script

### By Hand
1. Go to Project Settings -> General
2. Visibility
3. Change Project Visibility to Private

Also add the TA in your project
1. Go to ProjectSettings -> Members
2. Add Iacovos Kolokasis as a Developer

### Using the Script

The private.py script is written in [Python 3](https://www.python.org/). 
To run private.py script, please have 
**Python 3.4 or higher**, **Git 1.8 or higher** and **python-gitlab** installed.

* Install gitlab lib
```
pip3 install --upgrade python-gitlab --user
```

* Run the script
```
python3 private.py -t <personal token> -p <project_ id>
```
## Submission
* You should submit the source files of each assignment. Do not submit the object or executable file
* Commit all files (not executables or object files!)

```
git add file1.c file2.c file3.c
git commit -m "Commit message"
git push
```
