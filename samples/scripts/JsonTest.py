import Test
Test.use_json_flag = True

class JsonTestGeneratorMethods(Test.TestGeneratorMethods):
    pass

if __name__ == '__main__':
    Test.unittest.main(verbosity=2)