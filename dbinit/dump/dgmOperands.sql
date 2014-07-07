DROP TABLE IF EXISTS dgmOperands;
CREATE TABLE "dgmOperands" (
"operandID"  INTEGER NOT NULL,
"operandKey"  TEXT,
"description"  TEXT,
"format"  TEXT,
"arg1categoryID"  INTEGER,
"arg2categoryID"  INTEGER,
"resultCategoryID"  INTEGER,
"pythonFormat"  TEXT,
PRIMARY KEY ("operandID")
);

BEGIN TRANSACTION;
COMMIT TRANSACTION;
