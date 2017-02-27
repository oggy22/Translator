#include "stdafx.h"
#include "MockLanguage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(attribute_manager_test)
{
	using attr	= MockLanguage::attributes;
	using cat = MockLanguage::attribute_categories;

	TEST_METHOD(has_all_test)
	{
		translator::attribute_manager<MockLanguage>	am(attr::accus, attr::per3, attr::plur);
		translator::attribute_manager<MockLanguage>	am2(attr::accus, attr::per3, attr::negative);
		translator::attribute_manager<MockLanguage>	am_empty;

		Assert::IsTrue(am.has_all(am));
		Assert::IsFalse(am.has_all(am2));
		Assert::IsFalse(am2.has_all(am));
		Assert::IsTrue(am.has_all(am_empty));

		Assert::IsFalse(am_empty.has_all(am));
		Assert::IsFalse(am_empty.has_all(am2));
	}

	TEST_METHOD(accepts_test)
	{
		translator::attribute_manager<MockLanguage>	am(attr::accus, attr::per3, attr::plur);
		translator::attribute_manager<MockLanguage>	am2(attr::accus, attr::per3, attr::negative);
		translator::attribute_manager<MockLanguage>	am_empty;

		Assert::IsTrue(am.accepts(am));
		Assert::IsTrue(am.accepts(am2));
		Assert::IsTrue(am2.accepts(am));

		Assert::IsFalse(am.accepts(translator::attribute_manager<MockLanguage>(attr::accus, attr::sing)));
	}
};