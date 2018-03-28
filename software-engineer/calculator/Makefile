JC = javac
CLASSPATH = $$CLASSPATH:./libs/
LIBPATH = ./libs/

all: cal run

cal: RegularCal.java CalMain.java MatrixCal.java
	mkdir -p libs
	$(JC) -cp $(CLASSPATH)Jama.jar -d $(LIBPATH) MatrixCal.java
	$(JC) -d $(LIBPATH) RegularCal.java 
	$(JC) -classpath $(CLASSPATH)Jama.jar -d $(LIBPATH) CalMain.java

run:
	cd libs
	java -classpath $(CLASSPATH)Jama.jar CalMain
	cd ..

clean:
	rm $(LIBPATH)*.class