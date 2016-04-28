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
#pragma endregion

// Глаголи:
{ L"бити", глаг,{},
	{
		{ L"сам",{ једн, лиц1 } },
		{ L"си",{ једн, лиц2 } },
		{ L"је",{ једн, лиц3 } },
		{ L"смо",{ множ, лиц1 } },
		{ L"сте",{ множ, лиц2 } },
		{ L"су",{ множ, лиц3 } },
} },
{ L"волети", глаг },
{ L"видети", глаг },
{ L"гледати", глаг },
{ L"ићи",	глаг,{},
	{	{ L"иде",{ презосн } },
		{L"ишал", {перфосн} } }
},
{ L"играти",	глаг },
{ L"имати", глаг },
{ L"јести",	глаг, {},
	{ {L"једе", { презосн } },
	{ L"јел",{ перфосн } } }
},
{ L"морати", глаг },
{ L"моћи", глаг, {},
	{	{ L"може",{ презосн } }, { L"могу",{ једн, лиц1 } }, { L"могу",{ множ, лиц3 } },
		{ L"могал",{ перфосн } } }
},
{ L"певати", глаг,{} },
{ L"писати", глаг,{},
	{ { L"пише",{ презосн } } }
},
{ L"пити", глаг,{},{ {L"могал",{ перфосн } } } },
{ L"радити", глаг },
{ L"спавати", глаг },
{ L"учити", глаг },
{ L"хтети", глаг, {},
	{ { L"хоће",{ презосн } },{ L"хоћу",{ једн, лиц1 } } } },
{ L"читати", глаг,{} },

// Именице:
{ L"жена",	имен, { жен } },
{ L"коњ",	имен,{ муш, жив } },
{ L"корист",имен,{ жен } },
{ L"кост",	имен,{ жен } },
{ L"кућа",	имен, { жен } },
{ L"мачка", имен,{ жен } },
{ L"миш", имен,{ муш },{ { L"мишев",{ оснмнож } } } },
{ L"муж", имен,{ муш, жив } },
{ L"мушкарац", имен,{ муш, жив } },
{ L"орах", имен,{ муш } },
{ L"слон", имен,{ муш, жив }, {{L"слонов", {оснмнож}}} },
{ L"стена", имен,{ жен } },
{ L"сто", имен,{ муш },{ { L"столов",{ оснмнож } } } },
{ L"сунце", имен,{ сред } },
{ L"ташна", имен,{ жен } },
{ L"човек", имен,{ муш, жив },{ { L"људ",{ оснмнож } } } },
{ L"школа", имен, { жен } },

// Придеви:
{ L"брз", прид },
{ L"велики", прид },
{ L"глуп", прид },
{ L"добар", прид },
{ L"дуг", прид },
{ L"дугачак", прид },
{ L"јак", прид },
{ L"јефтин", прид },
{ L"кратак", прид },
{ L"леп", прид },
{ L"лош", прид },
{ L"мали", прид },
{ L"млад", прид },
{ L"паметан", прид },
{ L"плав", прид },
{ L"празан", прид },
{ L"пун", прид },
{ L"ружан", прид },
{ L"скуп", прид },
{ L"слаб", прид },

// Прилози:
{ L"брзо", прил,{}, { { L"брже", {комп} } } },
{ L"далеко",прил,{},{ { L"даље",{ комп } } } },
{ L"добро",прил,{},{ { L"боље",{ комп } } } },
{ L"касно", прил,{} },
{ L"лепо", прил,{},{ { L"лепше",{ комп } } } },
{ L"рано", прил,{} },
