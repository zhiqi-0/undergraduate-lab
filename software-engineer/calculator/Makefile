all: cal run

cal: RegularCal.java CalMain.java MatrixCal.java
	javac -cp Jama.jar MatrixCal.java
	javac CalMain.java

run:
	java -classpath $$CLASSPATH:Jama.jar CalMain

clean:
	rm *.class