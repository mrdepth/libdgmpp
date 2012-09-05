attach database :memory as eufe;
.read "./eufe.sql"
.backup eufe eufe.sqlite