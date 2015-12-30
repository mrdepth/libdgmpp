attach database :memory as dgmpp;
.read "./sql/copyTables.sql"
.backup dgmpp dgm.sqlite