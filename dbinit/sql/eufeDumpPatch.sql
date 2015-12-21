--Filter invTypes
delete from invCategories where categoryID not in (1, 2, 8, 18, 20, 7, 6, 16, 23, 32);
delete from invGroups where categoryID not in (select categoryID from invCategories);
delete from invTypes where groupID not in (select groupID from invGroups);
delete from dgmTypeAttributes where typeID not in (select typeID from invTypes);
delete from dgmTypeEffects where typeID not in (select typeID from invTypes);
delete from dgmEffects where effectID not in (select effectID from dgmTypeEffects);