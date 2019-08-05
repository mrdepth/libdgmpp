DROP TABLE IF EXISTS version;
CREATE TABLE "version" (
"build"  INTEGER NOT NULL,
"version"  TEXT,
PRIMARY KEY ("build"));
INSERT INTO version (build, version) VALUES (1544684, "17.06");
