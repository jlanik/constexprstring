cc_binary(
	name = "hello-world",
	srcs = ["hello_world.cpp"],
)

cc_library(
	name = "constexprstring",
	hdrs = ["constexprstring.h"]
)

cc_test(
	name = "test",
	srcs = ["test_constexprstring.cpp"],
	deps = [":constexprstring", 
			"@com_google_googletest//:gtest_main",
	]
)
