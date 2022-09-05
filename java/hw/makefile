JARFILE=hw.jar

run: build-jar
	java -jar $(JARFILE) 

build-jar: Manifest.txt build-class
	jar cfm hw.jar Manifest.txt HelloWorld.class

build-class: 
	javac HelloWorld.java 

clean:
	rm HelloWorld.class $(JARFILE)
