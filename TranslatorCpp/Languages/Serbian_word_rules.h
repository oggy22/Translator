﻿#pragma region Глаголи:
{ L"*ти", L"*ти", глаг, { инф } },
{ L"*ћи", L"*ћи", глаг, { инф } },

{ L"*", L"*м", глаг,{ лиц1, једн }, презосн },
{ L"*", L"*ш", глаг,{ лиц2, једн }, презосн },
{ L"*", L"*", глаг,{ лиц3, једн }, презосн },
{ L"*", L"*мо", глаг,{ лиц1, множ }, презосн },
{ L"*", L"*те", глаг,{ лиц2, множ }, презосн },
{ L"*а", L"*ају", глаг,{ лиц3, множ }, презосн },
{ L"*и", L"*е", глаг,{ лиц3, множ }, презосн },
{ L"*е", L"*у", глаг,{ лиц3, множ }, презосн },

{ L"*ти", L"*", глаг,{ презосн } },
{ L"*ети", L"*и", глаг,{ презосн } },
#pragma endregion

#pragma region Именице:
{ L"*", L"*", имен,{ једн, ном } },
{ L"*", L"*а", имен,{ једн, ген } },
{ L"*", L"*у", имен,{ једн, дат } },
{ L"*", L"*", имен,{ једн, акуз } },
{ L"*", L"*а", имен,{ једн, акуз }, жив },
{ L"*", L"*е", имен,{ једн, вок } },
{ L"*к", L"*че", имен,{ једн, вок } },
{ L"*", L"*", имен,{ једн, инстр } },
{ L"*", L"*у", имен,{ једн, лок } },

{ L"*", L"*и", имен,{ множ, ном }, оснмнож },
{ L"*", L"*а", имен,{ множ, ген }, оснмнож },
{ L"*", L"*има", имен,{ множ, дат }, оснмнож },
{ L"*", L"*е", имен,{ множ, акуз }, оснмнож },
{ L"*", L"*и", имен,{ множ, вок }, оснмнож },
{ L"*", L"*има", имен,{ множ, инстр }, оснмнож },
{ L"*", L"*има", имен,{ множ, лок }, оснмнож },

{ L"*", L"*", имен,{ оснмнож } },
{ L"*уж", L"*ужев", имен,{ оснмнож } }, //муж, пуж
{ L"*ац", L"*ц", имен,{ оснмнож } }, //мушкарац
{ L"*ао", L"*лов", имен,{ оснмнож } }, //орао, петао

{ L"*е", L"*а", имен,{ множ, ном } },
{ L"*е", L"*а", имен,{ множ, ген } },
{ L"*е", L"*има", имен,{ множ, дат } },
{ L"*е", L"*а", имен,{ множ, акуз } },
{ L"*е", L"*а", имен,{ множ, вок } },
{ L"*е", L"*има", имен,{ множ, инстр } },
{ L"*е", L"*има", имен,{ множ, лок } },

{ L"*еме", L"*емена", имен,{ множ, ном } },
{ L"*еме", L"*емена", имен,{ множ, ген } },
{ L"*еме", L"*еменима", имен,{ множ, дат } },
{ L"*еме", L"*емена", имен,{ множ, акуз } },
{ L"*еме", L"*емена", имен,{ множ, вок } },
{ L"*еме", L"*еменима", имен,{ множ, инстр } },
{ L"*еме", L"*еменима", имен,{ множ, лок } },

{ L"*", L"*а", имен,{ једн, ген }, оснједн },
{ L"*", L"*у", имен,{ једн, дат }, оснједн },
{ L"*", L"*у", имен,{ једн, лок }, оснједн },
{ L"*е", L"*е", имен,{ једн, акуз } },
{ L"*е", L"*а", имен,{ једн, акуз, жив } },
{ L"*е", L"*че", имен,{ једн, вок } },
{ L"*е", L"*ем", имен,{ једн, инстр } },
{ L"*еме", L"*еменом", имен,{ једн, инстр } },
									   
//орах, монах, влах
{ L"*х", L"*си", имен,{ множ, ном } },
{ L"*х", L"*сима", имен,{ множ, дат } },
{ L"*х", L"*си", имен,{ множ, вок } },
{ L"*х", L"*сима", имен,{ множ, инстр } },
{ L"*х", L"*сима", имен,{ множ, лок } },

{ L"*а", L"*а", имен,{ једн, ном } },
{ L"*а", L"*е", имен,{ једн, ген } },
{ L"*а", L"*и", имен,{ једн, дат } },
{ L"*а", L"*у", имен,{ једн, акуз } },
{ L"*а", L"*о", имен,{ једн, вок } },
{ L"*а", L"*ом", имен,{ једн, инстр } },
{ L"*а", L"*и", имен,{ једн, лок } },

{ L"*а", L"*е", имен,{ множ, ном } },
{ L"*а", L"*а", имен,{ множ, ген } },
{ L"*а", L"*ама", имен,{ множ, дат } },
{ L"*а", L"*е", имен,{ множ, акуз } },
{ L"*а", L"*е", имен,{ множ, вок } },
{ L"*а", L"*ама", имен,{ множ, инстр } },
{ L"*а", L"*ама", имен,{ множ, лок } },

{ L"*ст", L"*ст", имен,{ једн, ном } },
{ L"*ст", L"*сти", имен,{ једн, ген } },
{ L"*ст", L"*сти", имен,{ једн, дат } },
{ L"*ст", L"*ст", имен,{ једн, акуз } },
{ L"*ст", L"*сти", имен,{ једн, инстр } },

{ L"*ст", L"*сти", имен,{ множ, ном } },
{ L"*ст", L"*сти", имен,{ множ, ген } },
{ L"*ст", L"*стима", имен,{ множ, дат } },
{ L"*ст", L"*сти", имен,{ множ, акуз } },
{ L"*ст", L"*сти", имен,{ множ, инстр } },

{ L"*е", L"*ет", имен, { оснједн } }, //пиле
{ L"*ме", L"*мен", имен, { оснједн } }, //време, племен, теме
{ L"сунце", L"сунц", имен,{ оснједн } }, //сунце
#pragma endregion

#pragma region Прилози:
{ L"*", L"*",	прил,{ поз } },
{ L"*", L"нај*",прил,{ суп }, комп },
{ L"*о", L"*ије", прил,{ комп } }, //касно, рано
{ L"*го", L"*же", прил,{ комп } }, //дуго
{ L"*по", L"*пље", прил,{ комп } }, //глупо
{ L"*то", L"*ће", прил,{ комп } }, //жуто

{ L"велико", L"веће", прил,{ комп } },
{ L"кратко", L"краће", прил,{ комп } },
{ L"јако", L"јаче", прил,{ комп } },
{ L"лепо", L"лепше", прил,{ комп } },
{ L"мало", L"мање", прил,{ комп } },
{ L"црно", L"црње", прил,{ комп } },
#pragma endregion

#pragma region Придеви:
#include "Serbian_word_rules_adjectives.h"
{ L"*", L"*",		прид,{ оснпоз } },	//леп, глуп, лош
{ L"*ак", L"*к",	прид,{ оснпоз } },	//кратак,дугачак
{ L"јак", L"јак",	прид,{ оснпоз } },	//јак
{ L"*ан", L"*н",	прид,{ оснпоз } },	//паметан
{ L"*ар", L"*р",	прид,{ оснпоз } },	//добар, !стар
{ L"*и", L"*",		прид,{ оснпоз } },	//мали
{ L"стар", L"стар",	прид,{ оснпоз } },
#pragma endregion