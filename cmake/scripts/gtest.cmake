# CMake Script: include_gtest
# Contains a function with the same name 'include_gtest(URL)`
# the function takes a URL to the GTest repo for the ver of
# GTest the user wants to include into their project.

function(gtest gtest_zip_url)
  include(FetchContent)
  FetchContent_Declare(googletest URL ${gtest_zip_url})
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
endfunction()
