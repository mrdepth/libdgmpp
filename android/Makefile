SHELL:=/bin/sh

all: clean build publish

clean:
	./gradlew clean

build:
	./gradlew build

publish: build
	./gradlew publishToMavenLocal

