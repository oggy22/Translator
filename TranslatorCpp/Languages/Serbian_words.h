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
{ L"бацати", глаг, { прел, повр } },
{ L"бацити", глаг, { прел, повр } },
{ L"бирати", глаг,{ прел } },
{ L"бити", глаг, {},
	{
		{ L"сам",{ једн, лиц1 } },
		{ L"си",{ једн, лиц2 } },
		{ L"је",{ једн, лиц3 } },
		{ L"смо",{ множ, лиц1 } },
		{ L"сте",{ множ, лиц2 } },
		{ L"су",{ множ, лиц3 } },
} },
{ L"борити", глаг, { повр } },
{ L"бунити", глаг, { повр } },
{ L"васпитати", глаг,{ прел } },
{ L"везати", глаг,{ прел, повр } },
{ L"веровати", глаг,{ непрел } },
{ L"видети", глаг,{ прел, непрел } },
{ L"водити", глаг,{ прел, непрел } },
{ L"волети", глаг,{ прел } },
{ L"вратити", глаг,{ прел, повр } },
{ L"газити", глаг,{ прел, непрел } },
{ L"гледати", глаг, { прел, непрел } },
{ L"говорити", глаг, { непрел } },
{ L"дати", глаг, { прел }, { { L"даје", { презосн } } } },
{ L"дизати", глаг, { прел, непрел }, { { L"диже", { презосн } } } },
{ L"дувати", глаг, { прел, непрел } },
{ L"желети", глаг, { прел, мод } },
{ L"журити", глаг, { непрел, повр } },
{ L"закључати", глаг, { прел, повр } },
{ L"закључити", глаг, { мод2 } },
{ L"заразити", глаг,{ прел, повр } },
{ L"затворити", глаг, { прел } },
{ L"затварати", глаг, { прел } },
{ L"зевати", глаг, { непрел } },
{ L"знати", глаг, { прел, непрел, мод2 } },
{ L"значити", глаг,{ мод2 } },
{ L"ићи",	глаг, { непрел },
	{	{ L"иде",{ презосн } },
		{L"ишал", {перфосн} } }
},
{ L"играти", глаг, { прел, повр } },
{ L"имати", глаг,{ прел } },
{ L"јахати", глаг, { непрел, прел } },
{ L"јести",	глаг,{ прел, непрел } ,
	{ {L"једе", { презосн } },
	{ L"јел",{ перфосн } } }
},
{ L"казати", глаг, { прел, непрел, мод2} },
{ L"какити", глаг, { непрел } },
{ L"карати", глаг, { прел, непрел } },
{ L"кашљати", глаг, { непрел }, { { L"кашље", { презосн } } } },
{ L"кијати", глаг, { непрел } },
{ L"клањати", глаг,{ повр } },
{ L"копати", глаг, { прел, непрел } },
{ L"користити", глаг, { прел } },
{ L"кренути", глаг, { непрел }, { { L"крене", { презосн } } } },
{ L"кретати", глаг, { непрел, повр }, { { L"креће", { презосн } } } },
{ L"кувати", глаг, { прел, непрел } },
{ L"кукати", глаг, { непрел } },
{ L"купати", глаг, { прел, повр } },
{ L"лагати", глаг, { непрел } },
{ L"лежати", глаг, { непрел }, { { L"лежи", { презосн } } } },
{ L"ловити", глаг, { прел, непрел } },
{ L"љубити", глаг, { прел, повр } },
{ L"љуљати", глаг, { прел, повр } },
{ L"мазати", глаг, { прел, повр } },
{ L"махати", глаг, { непрел } },
{ L"мењати", глаг, { прел, повр } },
{ L"миловати", глаг, { прел, повр }, { { L"милује", { презосн } } } },
{ L"мислити", глаг, { непрел, мод2 } },
{ L"морати", глаг, { мод } },
{ L"моћи", глаг, { мод },
	{	{ L"може",{ презосн } }, { L"могу",{ једн, лиц1 } }, { L"могу",{ множ, лиц3 } },
		{ L"могал",{ перфосн } } }
},
{ L"мучити", глаг, { прел, повр } },
{ L"нападати", глаг, { прел, непрел } },
{ L"немати", глаг, { прел, непрел } },
{ L"нудити", глаг, { прел, повр } },
{ L"откључати", глаг, { прел } },
{ L"очекивати", глаг, { прел }, { { L"очекује", { презосн } } } },
{ L"падати", глаг, { непрел } },
{ L"пазити", глаг, { прел, непрел, повр } },
{ L"певати", глаг, { прел, непрел } },
{ L"пешачити", глаг, { непрел } },
{ L"плакати", глаг, { непрел }, { { L"плаче", { презосн } } } },
{ L"плашити", глаг, { прел, повр } },
{ L"писати", глаг, { прел, непрел } ,
	{ { L"пише",{ презосн } } }
},
{ L"питати", глаг, { прел, повр } },
{ L"пити", глаг,{ прел, непрел },
	{ {L"пије", { презосн } } } },
{ L"пишати", глаг, { прел, непрел } ,
	{ { L"пиша", { презосн } } }
},
{ L"победити", глаг, { прел, непрел } },
{ L"поклонити", глаг, { прел, повр } },
{ L"помагати", глаг, { непрел }, { { L"помаже", { презосн } } } },
{ L"поштовати", глаг, { прел, непрел }, { { L"поштује", { презосн } } } },
{ L"правити", глаг, { прел } },
{ L"прати", глаг, { прел, непрел }, { { L"пере", { презосн } } } },
{ L"пратити", глаг, { прел, непрел } },
{ L"прдети", глаг, { непрел } },
{ L"пробати", глаг, { прел, непрел } },
{ L"пумпати", глаг, { прел, непрел } },
{ L"пушити", глаг, { прел, непрел, повр } },
{ L"радити", глаг, { прел, непрел } },
{ L"ручати", глаг, { прел, непрел } },
{ L"сањати", глаг, { прел, непрел, мод2 } },
{ L"свирати", глаг, { прел, непрел } },
{ L"седети", глаг, { непрел } },
{ L"слушати", глаг, { прел, непрел } },
{ L"скакати", глаг, { непрел }, { { L"скаче", { презосн } } } },
{ L"смејати", глаг, { повр } },
{ L"смети", глаг, { мод } },
{ L"спавати", глаг, { непрел } },
{ L"срати", глаг, { прел, непрел }, { { L"сере", { презосн } } } },
{ L"терати", глаг, { прел } },
{ L"трчати", глаг, { непрел } },
{ L"ћутати", глаг, { непрел }, { { L"ћути", { презосн } } } },
{ L"узети", глаг, { прел }, { { L"узме", { презосн } } } },
{ L"узимати", глаг, { прел }, { { L"узима", { презосн } } } },
{ L"умети", глаг, { непрел, мод } },
{ L"учити", глаг, { прел, непрел } },
{ L"ходати",глаг, { непрел } },
{ L"хранити", глаг, { прел, повр } },
{ L"хтети", глаг, { прел, мод, мод2 } ,
	{ { L"хоће",{ презосн } },{ L"хоћу",{ једн, лиц1 } }, {L"хоће",{ множ, лиц3 } } } },
{ L"чувати", глаг, { прел, повр } },
{ L"читати", глаг, { прел, непрел } },
{ L"чути", глаг,{ прел, непрел, повр } ,
	{ { L"чује",{ презосн } } } },
{ L"шапутати", глаг, { непрел }, { { L"узима", { презосн } } } },
{ L"шетати", глаг, { прел, непрел, повр } },
{ L"шишати", глаг, { прел, повр } },
#pragma endregion

#pragma region Именице
{ L"адреса",имен, { жен} },
{ L"авион",	имен, { муш } },
{ L"ајкула",имен, { жен } },
{ L"баба",	имен, { жен, жив } },
{ L"бака",	имен, { жен, жив } },
{ L"багер", имен, { муш } },
{ L"балон", имен, { муш } },
{ L"банана",имен, { жен, жив } },
{ L"беба",	имен, { жен } },
{ L"биљка",	имен, { жен } },
{ L"благо", имен, { сред } },
{ L"бог",	имен, { муш }, { { L"богов", { оснмнож } } } },
{ L"бодља",	имен, { жен } },
{ L"боја",	имен, { жен } },
{ L"бол",	имен, { жен, мис } },
{ L"брада",	имен, { жен } },
{ L"брат",	имен, { муш, жив } },
{ L"бресква",	имен, { жен } },
{ L"брод",	имен, { муш }, { { L"бродов", { оснмнож } } } },
{ L"број",	имен, { муш }, { { L"бројев", { оснмнож } } } },
{ L"буба",	имен, { жен } },
{ L"будала",имен, { жен } },
{ L"буђ",	имен, { жен } },
{ L"бубамара",	имен, { жен } },
{ L"вакцина",	имен, { жен } },
{ L"вакцинација",	имен, { жен } },
{ L"вакцинисање",	имен, { сред } },
{ L"ватра",	имен, { жен }, { { L"ватри", { множ, ген } } } },
{ L"врат",	имен, { муш } },
{ L"виљушка",	имен, { жен } },
{ L"вино",  имен, { сред } },
{ L"вирус",	имен, { муш } },
{ L"вишња",	имен, { жен } },
{ L"вода",	имен, { жен } },
{ L"воз",	имен, { муш }, { { L"возов", { оснмнож } } } },
{ L"волан",	имен, { муш } },
{ L"време",	имен, { сред } },
{ L"вук",	имен, { муш }, { { L"вуков", { оснмнож } } } },
{ L"гавран",имен, { муш, жив }, { { L"гавранов", { оснмнож } } } },
{ L"гитара",имен, { жен } },
{ L"глава",имен,  { жен } },
{ L"година",имен, { жен } },
{ L"грана", имен, { жен } },
{ L"грло",	имен, { сред } },
{ L"гроб",	имен, { муш },{ { L"гробов",{ оснмнож } } } },
{ L"град",	имен, { муш, жив },{ { L"градов",{ оснмнож } } } },
{ L"гуза",	имен, { жен } },
{ L"гуска",	имен, { жен } },
{ L"дабар",	имен, { муш },{ { L"дабров", { оснмнож } } } },
{ L"дан",	имен, { муш } },
{ L"дар",	имен, { муш },{ { L"даров", { оснмнож } } } },
{ L"даска",	имен, { жен } },
{ L"деда",	имен, { муш, жив } },
{ L"дека",	имен, { муш, жив } },
{ L"дизалица",	имен, { жен } },
{ L"дим",	имен, { муш } },
{ L"дно",	имен, { сред } },
{ L"дом",	имен, { муш }, { { L"домов", { оснмнож } } } },
{ L"дрво",	имен, { сред }, { { L"дрвет", { оснједн } } } },
{ L"дуга",	имен, { жен } },
{ L"дрога",	имен, { жен } },
{ L"дуња",	имен, { жен } },
{ L"ђак",	имен, { муш, жив } },
{ L"ексер", имен, { муш } },
{ L"жаба",	имен, { жен } },
{ L"жена",	имен, { жен } },
{ L"живот",	имен, { муш } },
{ L"животиња",	имен,{ жен } },
{ L"завера",имен, { жен } },
{ L"зараза",имен, { жен } },
{ L"звезда",имен, { жен } },
{ L"зграда",имен, { жен } },
{ L"зец",	имен, { муш }, { { L"зечев", { оснмнож } } } },
{ L"зид",	имен, { муш }, { { L"зидов", { оснмнож } } } },
{ L"змија",	имен, { жен } },
{ L"знак",	имен, { муш }, { { L"знаков", { оснмнож } } } },
{ L"зуб",	имен, { муш } },
{ L"игла",	имен, { жен }, { { L"игала",{ множ, ген } } } },
{ L"игра",	имен, { жен }, { { L"игара",{ множ, ген } } } },
{ L"играчка",	имен, { жен } },
{ L"име",	имен, { сред }, { { L"имен", { оснмнож } } } },
{ L"јабука",имен, { жен } },
{ L"јаје",	имен, { сред } },
{ L"јелка",	имен, { жен } },
{ L"јеж",	имен, { муш }, { { L"јежев", { оснмнож } } } },
{ L"језик",	имен, { муш } },
{ L"јога",	имен, { жен } },
{ L"кава",	имен, { жен } },
{ L"камен",	имен, { муш },{ { L"каменов", { оснмнож } } } },
{ L"камила",имен, { жен } },
{ L"канализација",	имен, { жен } },
{ L"кафа",	имен, { жен } },
{ L"кацига",имен, { жен } },
{ L"кашика",имен, { муш } },
{ L"кева",	имен, { жен } },
{ L"кеса",	имен, { жен } },
{ L"киша",	имен, { жен } },
{ L"клавир",имен, { муш } },
{ L"кључ",	имен, { муш }, { { L"кључев", { оснмнож } } } },
{ L"кобра",	имен, { жен } },
{ L"ковид",	имен, { муш } },
{ L"колевка",  имен, { жен } },
{ L"колено",имен, { сред } },
{ L"коло",  имен, { сред } },
{ L"компјутер",	имен, { муш } },
{ L"коњ",	имен, { муш, жив } },
{ L"копно",	имен, { сред } },
{ L"корист",имен, { жен } },
{ L"корона",имен, { жен } },
{ L"коса",	имен, { жен } },
{ L"кост",	имен, { жен } },
{ L"коцка",	имен, { жен }, { { L"коцки", { множ, ген } } } },
{ L"крава",	имен, { жен } },
{ L"крај",	имен, { муш }, { { L"крајев", { оснмнож } } } },
{ L"краљ",	имен, { муш, жив },{ { L"краљев", { оснмнож } } } },
{ L"краљица",	имен, { жен, жив } },
{ L"кров",  имен, { муш }, { { L"кровов", { оснмнож } } } },
{ L"кромпир",	имен, { муш } },
{ L"крушка",	имен, { жен } },
{ L"кугла",	имен, { жен } },
{ L"кукуруз",имен, { муш } },
{ L"кула",	имен, { жен } },
{ L"кућа",	имен, { жен } },
{ L"лавеж", имен, { муш } },
{ L"лаж",	имен, { жен, мис } },
{ L"лампа",	имен, { жен, мис }, { { L"лампи", { множ, ген } } } },
{ L"лептир",имен, { муш } },
{ L"лисица",имен, { жен } },
{ L"лов",	имен, { муш }, { { L"ловов", { оснмнож } } } },
{ L"лонац", имен, { муш } },
{ L"лук",	имен, { муш }, { { L"луков", { оснмнож } } } },
{ L"лула",	имен, { жен } },
{ L"лутка",	имен, { жен } },
{ L"љубав", имен, { жен, мис } },
{ L"љуљашка",	имен, { жен } },
{ L"мајка", имен, { жен, жив } },
//{ L"мајица",имен, { жен } }, //маја->мајица
{ L"мајмун",имен, { муш } },
{ L"мама",	имен,  { жен, жив } },
{ L"маса",	имен, { жен } },
{ L"маска", имен, { жен } },
{ L"маца",	имен, { жен, жив } },
{ L"мачка", имен, { жен, жив } },
{ L"машина",имен, { жен } },
{ L"мед",	имен, { муш } },
{ L"месец", имен, { муш } },
{ L"метеж", имен, { муш } },
{ L"мирис", имен, { муш } },
{ L"мисао", имен, { жен, мис} },
{ L"мит",	имен, { муш } },
{ L"миш",	имен, { муш, жив },{ { L"мишев",{ оснмнож } } } },
{ L"млеко", имен, { сред } },
{ L"море",	имен,{ сред } },
{ L"мост",	имен,{ муш },{ { L"мостов",{ оснмнож } } } },
{ L"мотел", имен,{ муш } },
{ L"моћ",	имен, { жен, мис } },
{ L"мрежа", имен, { жен } },
{ L"муж",	имен, { муш, жив } },
{ L"мука",	имен, { жен } },
{ L"музика",имен, { жен } },
{ L"мушкарац", имен, { муш, жив } },
{ L"недеља", имен, { жен } },
{ L"нога",	имен, { жен } },
{ L"нож",	имен, { муш }, { { L"ножев", { оснмнож } } } },
{ L"ноћ",	имен, { жен, мис } },
{ L"нос", имен, { муш }, { { L"носев", { оснмнож } } } },
{ L"њушка", имен, { жен } },
{ L"образ", имен, { муш } },
{ L"обрва", имен, { жен } },
{ L"овца", имен, { жен } },
{ L"огледало", имен, { сред } },
{ L"ограда", имен, { жен } },
{ L"око", имен, { сред }, { { L"ок", { оснједн } }, { L"оч", { оснмнож } } } },
{ L"оловка", имен, { жен } },
{ L"орао", имен, { муш } },
{ L"орах", имен, { муш } },
{ L"ормар", имен,{ муш } },
{ L"особа",	имен, { жен, жив } },
{ L"отац",	имен,{ муш, жив }, { { L"оц", { оснједн } }, { L"очев", { оснмнож } } } },
{ L"палиндром",имен, { муш } },
{ L"паприка",имен, { жен } },
{ L"папуча", имен, { жен } },
{ L"пара",	имен, { жен } },
{ L"паста", имен, { жен } },
{ L"патика", имен, { жен } },
{ L"патка", имен, { жен }, { { L"патака", { множ, ген } } } },
{ L"пас",	имен, { муш, жив }, { { L"пс", { оснједн } }, { L"пс", { оснмнож } } } },
{ L"песма", имен, { жен } },
{ L"петао", имен, { муш } },
{ L"пиво", имен, { сред } },
{ L"пиле", имен, { сред } },
{ L"писмо", имен, { сред } },
{ L"планина", имен, { жен } },
{ L"племе",	имен, { сред } },
{ L"поклон",имен, { муш } },
{ L"полицајац", имен, { муш } },
{ L"поп",	имен, { муш, жив }, { { L"попов", { оснмнож } } } },
{ L"политика", имен, { жен } },
{ L"понуда", имен, { жен } },
{ L"породица", имен, { жен } },
{ L"праг", имен, { муш } },
{ L"принц",	имен, { муш, жив },{ { L"принчев", { оснмнож } } } },
{ L"принцеза",	имен, { жен, жив } },
{ L"природа", имен, { жен } },
{ L"прича", имен, { жен } },
{ L"прст", имен, { муш } },
{ L"птица", имен, { жен } },
{ L"пумпа",	имен, { жен } },
{ L"пуж",	имен, { муш, жив }, { { L"пужев", { оснмнож } } } },
{ L"пут",	имен, { муш }, { { L"путев", { оснмнож } } } },
{ L"рад",	имен, { муш }, { { L"радов", { оснмнож } } } },
{ L"разлог",имен, { муш } },
{ L"ракун", имен, { муш } },
{ L"рам",	имен, { муш }, { { L"рамов", { оснмнож } } } },
{ L"раме",	имен, { сред } },
{ L"ред",	имен, { муш }, { { L"редов", { оснмнож } } } },
{ L"река",	имен, { жен } },
{ L"риба",	имен, { жен } },
{ L"роба",	имен, { жен } },
{ L"ров",	имен, { муш }, { { L"ровов", { оснмнож } } } },
{ L"рог",	имен, { муш }, { { L"рогов", { оснмнож } } } },
{ L"рок",	имен, { муш }, { { L"роков", { оснмнож } } } },
{ L"рука",	имен, { жен } },
{ L"рупа",	имен, { жен } },
{ L"ручак",	имен, { муш }, { { L"ручков", { оснмнож } } } },
{ L"сала",	имен, { жен } },
{ L"сапун", имен, { муш } },
{ L"сат",	имен, { муш }, { { L"сатов", { оснмнож } } } },
{ L"сахрана",	имен, { жен } },
{ L"свет",	имен, { муш }, { { L"светов", { оснмнож } } } },
{ L"свећа",	имен, { жен } },
{ L"свиња",	имен, { жен } },
{ L"секира",имен, { жен } },
{ L"село",	имен,{ сред } },
{ L"семе",	имен,{ сред } },
{ L"сено",	имен,{ сред } },
{ L"сестра",имен, { жен, жив } },
{ L"сијалица", имен, { жен } },
{ L"син",	имен, { муш, жив }, { { L"синов",{ оснмнож } } } },
{ L"сиса",	имен, { жен } },
{ L"ситуација", имен, { жен } },
{ L"сир",	имен, { муш, жив }, { { L"сирев",{ оснмнож } } } },
{ L"слово", имен, { сред } },
{ L"слон",	имен, { муш, жив }, { { L"слонов",{ оснмнож } } } },
{ L"смрт",	имен, { жен, мис } },
{ L"снага", имен, { жен } },
{ L"соба",	имен, { жен } },
{ L"сова",	имен, { жен, жив } },
{ L"сок",	имен, { муш, жив }, { { L"соков", { оснмнож } } } },
{ L"среда", имен, { жен } },
{ L"средина", имен, { жен } },
{ L"срећа", имен, { жен } },
{ L"ствар",	имен, { жен, мис } },
{ L"стена", имен, { жен } },
{ L"страна",имен, { жен } },
{ L"страх",	имен, { муш }, { { L"страхов", { оснмнож } } } },
{ L"стрина",имен, { жен } },
{ L"сто",	имен, { муш, жив }, { { L"столов", { оснмнож } } } },
{ L"столица", имен, { жен } },
{ L"стопало", имен, { сред } },
{ L"суд",	имен, { жен }, { { L"судов", { оснмнож } } } },
{ L"субота",имен, { жен } }, 
{ L"сунце", имен, { сред } },
{ L"талас", имен, { муш } },
{ L"тањир", имен, { муш } },
{ L"тата",	имен, { муш, жив } },
{ L"ташна", имен, { жен } },
{ L"телефон",	имен, { муш } },
{ L"тело",	имен, { сред } },
{ L"тета",	имен, { жен, жив } },
{ L"тетка", имен, { жен, жив } },
{ L"топ",	имен, { сред }, { { L"топов", { оснмнож } } } },
{ L"торта", имен, { жен } },
{ L"трава", имен, { жен } },
{ L"труба", имен, { жен } },
{ L"ћерка", имен, { жен, жив } },
{ L"ћурка", имен, { жен, жив } },
{ L"уво",	имен, { сред }, { { L"уш", { оснмнож } } } },
{ L"удица", имен, { жен } },
{ L"улица", имен, { жен, жив } },
{ L"унук",	имен, { муш, жив } },
{ L"унука", имен, { жен, жив } },
{ L"фабрика",имен,{ жен } },
{ L"фарба", имен, { жен } },
{ L"флаша", имен, { жен } },
{ L"фока",	имен, { жен } },
{ L"фотеља",имен, { жен } },
{ L"хлеб",  имен, { муш }, { { L"хлебов", { оснмнож } } } },
{ L"хотел", имен, { муш } },
{ L"храна",	имен, { жен } },
{ L"цар",	имен, { муш }, { { L"царев", { оснмнож } } } },
{ L"царица",имен, { жен } },
{ L"цвет",	имен, { муш }, { { L"цветов", { оснмнож } } } },
{ L"цигара",имен, { жен } },
{ L"ципела",имен, { жен } },
{ L"цица",	имен, { жен } },
{ L"чарапа",имен, { жен } },
{ L"чекић", имен, { муш } },
{ L"чело",	имен, { сред } },
{ L"чизма", имен, { жен } },
{ L"човек", имен, { муш, жив }, { { L"људ", { оснмнож } } } },
{ L"џак",	имен, { муш }, { { L"џаков", { оснмнож } } } },
{ L"џем",	имен, { муш }, { { L"џемов", { оснмнож } } } },
{ L"џеп",	имен, { муш }, { { L"џепов", { оснмнож } } } },
{ L"џин",	имен, { муш, жив }, { { L"џинов", { оснмнож } } } },
{ L"џунгла",имен, { жен } },
{ L"шака",	имен, { жен } },
{ L"шал",	имен, { муш }, { { L"шалов", { оснмнож } } } },
{ L"шала",	имен, { жен } },
{ L"шапа",	имен, { жен } },
{ L"шаргарепа",	имен, { жен } },
{ L"шахт",	имен, { муш }, { { L"шахтов", { оснмнож } } } },
{ L"шешир", имен, { муш } },
{ L"школа", имен, { жен } },
{ L"шкољка",	имен, { жен } },
{ L"шлем",	имен, { муш }, { { L"шлемов", { оснмнож } } } },
{ L"шума",	имен, { жен } },

// Imena:
{ L"ана", имен, { жен, жив }, { { L"ана",{ једн, вок } } } },
{ L"ања", имен, { жен, жив }, { { L"ања",{ једн, вок } } } },
{ L"аца", имен, { жен, жив } },
{ L"бојан", имен, { муш, жив } },
{ L"бојана", имен, { жен, жив } },
{ L"горан", имен, { муш, жив } },
{ L"горана", имен, { жен, жив } },
{ L"дејан", имен, { муш, жив } },
{ L"дејана", имен, { жен, жив } },
{ L"драган", имен, { муш, жив } },
{ L"драгана", имен, { жен, жив } },
{ L"ена", имен, { жен, жив } },
{ L"ема", имен, { жен, жив } },
{ L"зоран", имен, { муш, жив } },
{ L"зорана", имен, { жен, жив } },
{ L"ива",	имен, { жен, жив } },
{ L"јован", имен, { муш, жив }, { { L"јован", { оснједн } } } },
{ L"јована", имен, { жен, жив } },
{ L"лука",	имен, { муш, жив } },
{ L"маја",	имен, { жен, жив } },
{ L"максим", имен, { муш, жив } },
{ L"марија", имен, { жен, жив } },
{ L"марина", имен, { жен, жив } },
{ L"марица", имен, { жен, жив }, { { L"марице",{ једн, вок } } } },
{ L"милица", имен, { жен, жив }, { { L"милице",{ једн, вок } } } },
{ L"милован", имен, { муш, жив }, { { L"милован", { оснједн } } } },
{ L"милош", имен, { муш, жив } },
{ L"мира",	имен, { жен, жив } },
{ L"мирјана", имен, { жен, жив } },
{ L"нада",	имен, { жен, жив } },
{ L"неда",	имен, { муш, жив } },
{ L"невен", имен, { муш, жив } },
{ L"невена",имен, { жен, жив } },
{ L"немања",имен, { муш, жив } },
{ L"новак", имен, { муш, жив } },
{ L"огњен", имен, { муш, жив } },
{ L"оља",	имен, { жен, жив }, { { L"оља", { једн, вок } } } },
{ L"софија",имен, { жен, жив } },
{ L"уна",	имен, { жен, жив }, { { L"уна", { једн, вок } } } },

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

#pragma region Придеви језици, државе
{ L"амерички", прид },
{ L"босански", прид },
{ L"британски", прид },
{ L"бугарски", прид },
{ L"грчки", прид },
{ L"енглески", прид },
{ L"италијански", прид },
{ L"јапански", прид },
{ L"канадски", прид },
{ L"кинески", прид },
{ L"мађарски", прид },
{ L"македонски", прид },
{ L"мексички", прид },
{ L"немачки", прид },
{ L"словеначки", прид },
{ L"српски", прид },
{ L"пољски", прид },
{ L"португалски", прид },
{ L"румунски", прид },
{ L"руски", прид },
{ L"француски", прид },
{ L"хрватски", прид },
{ L"црногорски", прид },
{ L"шпански", прид },
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
{ L"а", остл },
{ L"али", остл },
{ L"и", остл },
{ L"или", остл },
{ L"ма", остл },

// Prilozi
{ L"без", остл },
{ L"за", остл },
{ L"на", остл },
{ L"о", остл },
{ L"око", остл },
{ L"са", остл },
{ L"у", остл },

// Uzvici
{ L"ах", остл },
{ L"ех", остл },
{ L"хеј", остл },
{ L"ух",остл },

#pragma endregion