JC = javac

all: UI

UI: RegStat.java Buffer.java Reservation.java Tomasulo.java UI.java
	$(JC) RegStat.java Buffer.java Reservation.java Tomasulo.java UI.java

tomasulo: RegStat.java Buffer.java Reservation.java Tomasulo.java
	$(JC) Tomasulo.java RegStat.java Buffer.java Reservation.java

run:
	java Tomasulo

clean:
	rm *.class