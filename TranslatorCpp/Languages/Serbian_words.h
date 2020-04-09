﻿#pragma region Заменице
{ L"ја", зам, { једн, лиц1 },
{
	{ L"ја",{ ном } },
	{ L"мене",{ ген } },
	{ L"мени",{ дат } },
	{ L"мене",{ акуз } }
} },
{ L"ти", зам,{ једн, лиц2 },
{
	{ L"ти",{ ном } },
	{ L"тебе",{ ген } },
	{ L"теби",{ дат } },
	{ L"тебе",{ акуз } },
} },
{ L"он", зам,{ једн, лиц3, муш },
{
	{ L"он",{ ном } },
	{ L"њега",{ ген } },
	{ L"њему",{ дат } },
	{ L"њега",{ акуз } },
} },
{ L"она", зам,{ једн, лиц3, жен },
{
	{ L"она",{ ном } },
	{ L"ње",{ ген } },
	{ L"њој",{ дат } },
	{ L"њу",{ акуз } },
} },
{ L"оно", зам,{ једн, лиц3, сред },
{
	{ L"он",{ ном } },
	{ L"њега",{ ген } },
	{ L"њему",{ дат } },
	{ L"њега",{ акуз } },
} },
{ L"ми", зам,{ множ, лиц1 },
{
	{ L"ми",{ ном } },
	{ L"нас",{ ген } },
	{ L"нама",{ дат } },
	{ L"нас",{ акуз } }
} },
{ L"ви", зам,{ множ, лиц2 },
{
	{ L"ви",{ ном } },
	{ L"вас",{ ген } },
	{ L"вама",{ дат } },
	{ L"вас",{ акуз } },
} },
{ L"они", зам,{ множ, лиц3, муш },
{
	{ L"они",{ ном } },
	{ L"њих",{ ген } },
	{ L"њима",{ дат } },
	{ L"њих",{ акуз } },
} },
{ L"оне", зам,{ множ, лиц3, жен },
{
	{ L"оне",{ ном } },
	{ L"њих",{ ген } },
	{ L"њима",{ дат } },
	{ L"њих",{ акуз } },
} },
{ L"она", зам,{ множ, лиц3, сред },
{
	{ L"она",{ ном } },
	{ L"њих",{ ген } },
	{ L"њима",{ дат } },
	{ L"њих",{ акуз } },
} },
#pragma endregion

#pragma region Глаголи
{ L"бирати", глаг,{ прел } },
{ L"бити", глаг,{},
	{
		{ L"сам",{ једн, лиц1 } },
		{ L"си",{ једн, лиц2 } },
		{ L"је",{ једн, лиц3 } },
		{ L"смо",{ множ, лиц1 } },
		{ L"сте",{ множ, лиц2 } },
		{ L"су",{ множ, лиц3 } },
} },
{ L"васпитати", глаг,{ прел } },
{ L"видети", глаг,{ прел } },
{ L"волети", глаг,{ прел } },
{ L"гледати", глаг,{ прел } },
{ L"говорити", глаг },
{ L"желети", глаг,{ прел } },
{ L"заразити", глаг,{ прел } },
{ L"знати", глаг },
{ L"значити", глаг,{ прел } },
{ L"ићи",	глаг,{},
	{	{ L"иде",{ презосн } },
		{L"ишал", {перфосн} } }
},
{ L"играти", глаг },
{ L"имати", глаг,{ прел } },
{ L"јести",	глаг,{ прел } ,
	{ {L"једе", { презосн } },
	{ L"јел",{ перфосн } } }
},
{ L"казати", глаг,{},
	{ { L"каже",{ презосн } } } },
{ L"копати", глаг },
{ L"користити", глаг, { прел } },
{ L"кувати", глаг, { прел } },
{ L"ловити", глаг, { прел } },
{ L"љубити", глаг, { прел } },
{ L"љуљати", глаг, { прел } },
{ L"мазати", глаг,{ прел },
	{ { L"маже",{ презосн } } } },
{ L"мењати", глаг,{ прел } },
{ L"миловати", глаг, { прел }, { { L"милује", { презосн } } } },
{ L"морати", глаг },
{ L"моћи", глаг, {},
	{	{ L"може",{ презосн } }, { L"могу",{ једн, лиц1 } }, { L"могу",{ множ, лиц3 } },
		{ L"могал",{ перфосн } } }
},
{ L"немати", глаг,{ прел } },
{ L"пазити", глаг,{ прел } },
{ L"певати", глаг,{ прел } },
{ L"плашити", глаг, { прел } },
{ L"писати", глаг,{ прел } ,
	{ { L"пише",{ презосн } } }
},
{ L"питати", глаг,{ прел } },
{ L"пити", глаг,{ прел },
	{ {L"пије", { презосн } } } },
{ L"победити", глаг, { прел } },
{ L"поклонити", глаг, { прел } },
{ L"правити", глаг, { прел } },
{ L"пратити", глаг, { прел } },
{ L"радити", глаг, { прел } },
{ L"сањати", глаг, { прел } },
{ L"свирати", глаг, { прел } },
{ L"слушати", глаг, { прел } },
{ L"спавати", глаг },
{ L"срати", глаг, {}, { { L"сере", { презосн } } } },
{ L"ћутати", глаг, {}, { { L"ћути", { презосн } } } },
{ L"узети", глаг, { прел }, { { L"узме", { презосн } } } },
{ L"узимати", глаг, { прел }, { { L"узима", { презосн } } } },
{ L"умети", глаг },
{ L"учити", глаг },
{ L"хтети", глаг, { прел } ,
	{ { L"хоће",{ презосн } },{ L"хоћу",{ једн, лиц1 } }, {L"хоће",{ множ, лиц3 } } } },
{ L"чувати", глаг, { прел } },
{ L"читати", глаг, { прел } },
{ L"чути", глаг,{ прел } ,
	{ { L"чује",{ презосн } } } },
{ L"шетати", глаг },
{ L"шишати", глаг, { прел } },
#pragma endregion

#pragma region Именице
{ L"авион",	имен,{ муш } },
{ L"баба",	имен,{ жен, жив } },
{ L"бака",	имен,{ жен, жив } },
{ L"банана",имен,{ жен, жив } },
{ L"беба",	имен,{ жен } },
{ L"благо", имен,{ сред } },
{ L"бог",	имен,{ муш }, { { L"богов", { оснмнож } } } },
{ L"брат",	имен,{ муш, жив } },
{ L"брод",	имен, { муш }, { { L"бродов", { оснмнож } } } },
{ L"буба",	имен,{ жен } },
{ L"град", имен,{ муш, жив },{ { L"градов",{ оснмнож } } } },
{ L"ватра",	имен, { жен } },
{ L"вино",  имен,{ сред } },
{ L"вирус",	имен, { муш } },
{ L"вода",	имен, { жен } },
{ L"време",	имен,{ сред } },
{ L"вук",	имен, { муш }, { { L"вуков", { оснмнож } } } },
{ L"дан",	имен,{ муш } },
{ L"дар",	имен,{ муш },{ { L"даров", { оснмнож } } } },
{ L"деда",	имен,{ муш, жив } },
{ L"дрво",	имен,{ сред } },
{ L"дуга",	имен,{ жен } },
{ L"жена",	имен, { жен } },
{ L"живот",	имен,{ муш } },
{ L"зараза",имен, { жен } },
{ L"зец",	имен, { муш }, { { L"зечев", { оснмнож } } } },
{ L"име",	имен, { сред }, { { L"имен", { оснмнож } } } },
{ L"јабука",имен, { жен } },
{ L"јаје",	имен,{ сред } },
{ L"камила",имен,{ жен } },
{ L"коњ",	имен,{ муш, жив } },
{ L"корист",имен,{ жен } },
{ L"корона",имен,{ жен } },
{ L"кост",	имен,{ жен } },
{ L"крава",	имен, { жен } },
{ L"краљ",	имен,{ муш, жив },{ { L"краљев", { оснмнож } } } },
{ L"краљица",	имен,{ жен, жив } },
{ L"кромпир",	имен,{ муш } },
{ L"кућа",	имен,{ жен } },
{ L"љубав", имен,{ жен } },
{ L"мајка", имен,{ жен, жив } },
{ L"мама", имен,{ жен, жив } },
{ L"маса", имен,{ жен } },
{ L"маца", имен,{ жен } },
{ L"мачка", имен,{ жен } },
{ L"мирис", имен,{ муш, жив } },
{ L"миш", имен,{ муш },{ { L"мишев",{ оснмнож } } } },
{ L"мост", имен,{ муш, жив },{ { L"мостов",{ оснмнож } } } },
{ L"муж", имен,{ муш, жив } },
{ L"мушкарац", имен,{ муш, жив } },
{ L"недеља", имен,{ жен } },
{ L"нога", имен,{ жен } },
{ L"око", имен,{ сред }, { { L"ок", { оснједн } }, { L"оч", { оснмнож } } } },
{ L"орао", имен,{ муш } },
{ L"орах", имен,{ муш } },
{ L"ормар", имен,{ муш } },
{ L"отац",	имен,{ муш, жив }, { { L"оц", { оснједн } }, { L"очев", { оснмнож } } } },
{ L"паприка", имен, { жен } },
{ L"папуча", имен, { жен } },
{ L"пас",	имен,{ муш, жив }, { { L"пс", { оснједн } }, { L"пс", { оснмнож } } } },
{ L"песма", имен,{ жен } },
{ L"петао", имен,{ муш } },
{ L"пиво", имен,{ сред } },
{ L"пиле", имен,{ сред } },
{ L"планина", имен,{ жен } },
{ L"племе",	имен,{ сред } },
{ L"поклон",имен,{ муш } },
{ L"полицајац", имен,{ муш } },
{ L"поп",	имен,{ муш, жив },{ { L"попов", { оснмнож } } } },
{ L"породица", имен,{ жен } },
{ L"принц",	имен,{ муш, жив },{ { L"принчев", { оснмнож } } } },
{ L"принцеза",	имен,{ жен, жив } },
{ L"природа", имен,{ жен } },
{ L"птица", имен,{ жен } },
{ L"пуж", имен,{ муш, жив } },
{ L"рад", имен,{ муш },{ { L"радов", { оснмнож } } } },
{ L"рам", имен,{ муш },{ { L"рамов", { оснмнож } } } },
{ L"река", имен,{ жен } },
{ L"риба", имен,{ жен } },
{ L"роба", имен,{ жен } },
{ L"рок", имен,{ муш },{ { L"роков", { оснмнож } } } },
{ L"рука", имен,{ жен } },
{ L"секира",имен, { жен } },
{ L"семе",	имен,{ сред } },
{ L"сено",	имен,{ сред } },
{ L"свет",	имен, { муш },{ { L"светов", { оснмнож } } } },
{ L"свећа",	имен, { жен } },
{ L"свиња",	имен, { жен } },
{ L"село", имен,{ сред } },
{ L"сестра",имен,{ жен, жив } },
{ L"син", имен,{ муш, жив },{ { L"синов",{ оснмнож } } } },
{ L"сиса", имен,{ жен } },
{ L"сир", имен,{ муш, жив },{ { L"сирев",{ оснмнож } } } },
{ L"слон", имен,{ муш, жив },{ { L"слонов",{ оснмнож } } } },
{ L"сок", имен,{ муш, жив },{ { L"соков",{ оснмнож } } } },
{ L"среда", имен,{ жен } },
{ L"средина", имен,{ жен } },
{ L"стена", имен,{ жен } },
{ L"стрина", имен,{ жен } },
{ L"сто", имен,{ муш, жив },{ { L"столов",{ оснмнож } } } },
{ L"субота", имен,{ жен } },
{ L"сунце", имен,{ сред } },
{ L"тата", имен,{ муш, жив } },
{ L"тета", имен,{ жен } },
{ L"тетка", имен,{ жен } },
{ L"торта", имен,{ жен } },
{ L"ћерка", имен,{ жен, жив } },
{ L"ћурка", имен,{ жен, жив } },
{ L"ташна", имен,{ жен } },
{ L"трава", имен,{ жен } },
{ L"улица", имен,{ жен, жив } },
{ L"унук", имен,{ муш, жив } },
{ L"унука", имен,{ жен, жив } },
{ L"ципела", имен, { жен } },
{ L"чарапа", имен, { жен } },
{ L"чизма", имен, { жен } },
{ L"човек", имен,{ муш, жив },{ { L"људ",{ оснмнож } } } },
{ L"џак", имен,{ муш, жив },{ { L"џаков",{ оснмнож } } } },
{ L"џин", имен,{ муш, жив },{ { L"џинов",{ оснмнож } } } },
{ L"шешир", имен, { муш } },
{ L"школа", имен, { жен } },

// Imena:
{ L"ана", имен, { жен, жив }, { { L"ана",{ једн, вок } } } },
{ L"ања", имен, { жен, жив }, { { L"ања",{ једн, вок } } } },
{ L"аца", имен, { жен, жив } },
{ L"дејан", имен, { муш, жив } },
{ L"драган", имен, { муш, жив } },
{ L"ена", имен, { жен, жив } },
{ L"ема", имен, { жен, жив } },
{ L"ива", имен, { жен, жив } },
{ L"јован", имен, { муш, жив }, { { L"јован", { оснједн } } } },
{ L"лука", имен, { муш, жив } },
{ L"максим", имен, { муш, жив } },
{ L"марија", имен, { жен, жив } },
{ L"марина", имен, { жен, жив } },
{ L"марица", имен, { жен, жив }, { { L"марице",{ једн, вок } } } },
{ L"милица", имен, { жен, жив }, { { L"милице",{ једн, вок } } } },
{ L"милован", имен, { муш, жив }, { { L"милован", { оснједн } } } },
{ L"милош", имен, { муш, жив } },
{ L"мира", имен, { жен, жив } },
{ L"мирјана", имен, { жен, жив } },
{ L"невен", имен, { муш, жив } },
{ L"новак", имен, { муш, жив } },
{ L"немања", имен, { муш, жив } },
{ L"огњен", имен, { муш, жив } },
{ L"оља", имен, { жен, жив }, { { L"оља",{ једн, вок } } } },
{ L"нада", имен, { жен, жив } },

#pragma endregion

#pragma region Придеви
{ L"бел", прид },
{ L"брз", прид },
{ L"велик", прид },
{ L"глуп", прид },
{ L"гол", прид, {}, { {L"го", {муш, једн, ном} } } },
{ L"добар", прид },
{ L"дуг", прид },
{ L"дугачак", прид },
{ L"жут", прид },
{ L"зелен", прид },
{ L"јак", прид },
{ L"јефтин", прид },
{ L"кратак", прид },
{ L"леп", прид },
{ L"лош", прид, {}, { {L"лошег", {муш, једн, ген} } } },
{ L"мали", прид },
{ L"млад", прид },
{ L"паметан", прид },
{ L"плав", прид },
{ L"празан", прид },
{ L"пун", прид },
{ L"ружан", прид },
{ L"сам", прид },
{ L"скуп", прид },
{ L"слаб", прид },
{ L"спор", прид },
{ L"стар", прид },
{ L"црвен", прид },
{ L"црн", прид },
#pragma endregion

#pragma region Прилози
//{ L"брзо", прил,{}, { { L"брже", {комп} } } },
{ L"далеко",прил,{},{ { L"даље",{ комп } } } },
{ L"добро",прил,{},{ { L"боље",{ комп } } } },
{ L"касно", прил,{} },
//{ L"лепо", прил,{},{ { L"лепше",{ комп } } } },
{ L"полако", прил,{} },
{ L"рано", прил,{} },
#pragma endregion

#pragma region Остало
{ L"ако", остл },
{ L"да", остл },
{ L"јок", остл },
{ L"како", остл },
{ L"ли", остл },
{ L"не", остл },
{ L"сад", остл },
{ L"сада", остл },

// Veznici
{ L"али", остл },
{ L"и", остл },
{ L"или", остл },
{ L"ма", остл },

// Prilozi
{ L"без", остл },
{ L"за", остл },
{ L"о", остл },
{ L"са", остл },

// Uzvici
{ L"ах", остл },
{ L"ех", остл },
{ L"хеј", остл },
{ L"ух",остл },

#pragma endregion