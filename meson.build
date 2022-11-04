project('aerokit', 'c',
  version : '0.1',
  default_options : ['warning_level=3','c_std=c11'])

# Includes
external_headers = include_directories('external')
public_headers = include_directories(
  [
    'src/core/',
    'src/display/',
  ]
)

# TODO: Separate application/ into another library
# Libraries
aerolib = static_library(
  'aerolib',
  [
    'src/core/numerical_integration.c',
    'src/display/init.c',
    'src/application/asen3111_ca1_p1.c',
  ],
  install : true)

# Dependencies
sdl2_dep = dependency('sdl2')
math = meson.get_compiler('c').find_library('m', required: true)

# Executable
exe = executable(
  'aerokit',
  'aerokit.c',
  link_with: aerolib,
  include_directories: [public_headers, external_headers],
  dependencies: [sdl2_dep,math],
  install : true)

# Tests
numerical_tests = executable(
  'unitTests_NumericalIntegration.test',
  'tests/core/test_numerical_integration.c',
  link_with: aerolib,
  include_directories: [public_headers, external_headers],
  dependencies: [math]
)
test('Unit Tests NumericalIntegration', numerical_tests)

application_tests = executable(
  'unitTests_Application.test',
  'tests/application/test_asen3111_ca1_p1.c',
  link_with: aerolib,
  include_directories: [public_headers, external_headers],
  dependencies: [math]
)
test('Unit Tests Application', application_tests)
