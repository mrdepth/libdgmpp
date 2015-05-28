attach database :memory as eufe;
.read "./sql/copyTables.sql"
.backup eufe eufe.sqlite