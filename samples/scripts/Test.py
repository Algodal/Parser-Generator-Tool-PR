import unittest
import os
import subprocess
import sys

use_json_flag = False

root = '../data/test-data/'
test = '../build/Debug/TestOutput'

def c(name):
     return f'{name}.c'

def t(name, folder=None):
    if folder:
         return os.path.join(folder, name) 
    return os.path.join(test, name) 

def w(name):
	if os.name == 'nt':
		return os.path.splitext(name)[0] + '.exe'
	return name

def p(name):
    return os.path.join(root, name)

def generate(pathname, name, flags=None):
    if not os.path.exists(pathname):
        print(f"ERROR: {pathname} doesn't exist!")
        return False

    args = []
    if flags:
        temp_args = [w('../build/Debug/Console'), pathname]
        temp_args.extend(flags.split())
        args.extend(temp_args)
    else:
        args.extend([
            w('../build/Debug/Console'), 
            pathname,
            f'-n{name}',
            '-f', t(''),
            '--no-print'
        ])
    if use_json_flag:
        args.extend(['--json', '--json-support', '--json-main'])
    #print(args)
    return subprocess.run(args).returncode == 0

def compile(name, folder = None):
    args = [
        w('gcc'), 
        t(c(name), folder),
        '-o', t(w(name))
    ]
    return subprocess.run(args).returncode == 0

def run(name, text):
    args = [
        t(w(name)), 
        text
    ]
    if use_json_flag:
        args.extend([f'{test}/{name}-program.json'])
    #print(f'run args: {args}')
    return subprocess.run(args).returncode == 0


def program(flags, source, text, folder=None):
    source = p(source)
    text = p(text)
    name = os.path.splitext(os.path.basename(source))[0]
    generate(source, name, flags)

@unittest.skip("Validation Test")
class TestValidation(unittest.TestCase):
    def validate(self, sourceFilePath, result=True):
        source = p(sourceFilePath)
        name = os.path.splitext(os.path.basename(source))[0]
        self.assertEqual(generate(source, name), result)
        pass
    
    def test_00_validate(self):
        self.validate('lang/validate/validate_syntax_tokenizer_fail.parser', False)
        self.validate('lang/validate/validate_syntax_tokenizer_entrypoint_fail.parser', False)
        self.validate('lang/validate/validate_syntax_defined_fail.parser', False)
        self.validate('lang/validate/validate_syntax_command_fail.parser', False)
        self.validate('lang/validate/validate_fail_unique_define.parser', False)
        self.validate('lang/validate/validate_fail_defined_define.parser', False)
        self.validate('lang/validate/validate_fail_unique_variable.parser', False)
        self.validate('lang/validate/validate_fail_defined_variable.parser', False)
        
#@unittest.skip("Main Test")
class TestGeneratorMethods(unittest.TestCase):

    def process(self, sourceFilePath, textFilePath, result=True):
        source = p(sourceFilePath)
        text = p(textFilePath)
        name = os.path.splitext(os.path.basename(source))[0]

        self.assertTrue(generate(source, name))
        self.assertTrue(compile(name))
        #print(f'name: {name}, text: {text}')
        #actual = run(name, text)
        #print(f'EXPECTED RESULT: {result}, ACTUAL RESULT {actual}')
        #self.assertEqual(actual, result)
        self.assertEqual(run(name, text), result)
    
    def fixing(self):
        self.process('lang/basics/arith_gt_tokenphase.parser', 'text/basics/alphabet_uppercase')

    def test_01_basics(self):
        self.process('lang/basics/char.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/oneof.parser', 'text/basics/1.txt')
        self.process('lang/basics/exact.parser', 'text/basics/1.txt')
        self.process('lang/basics/order.parser', 'text/basics/1.txt')

        self.process('lang/basics/oneof.parser', 'text/basics/3.txt', False)
        self.process('lang/basics/exact.parser', 'text/basics/3.txt', False)
        self.process('lang/basics/order.parser', 'text/basics/3.txt', False)
    
    def test_02_basics(self):
        self.process('lang/basics/count_char.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_oneof.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_exact.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_order.parser', 'text/basics/1.txt')

        self.process('lang/basics/count_char_2.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_oneof_2.parser', 'text/basics/1.txt')

        self.process('lang/basics/count_char_r.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_oneof_r.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_exact_r.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_order_r.parser', 'text/basics/1.txt')

        self.process('lang/basics/count_char_ra.parser', 'text/basics/1.txt')        
        self.process('lang/basics/count_oneof_ra.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_exact_ra.parser', 'text/basics/1.txt')        
        self.process('lang/basics/count_order_ra.parser', 'text/basics/1.txt')

        self.process('lang/basics/count_char_ro.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_oneof_ro.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_exact_ro.parser', 'text/basics/1.txt')
        self.process('lang/basics/count_order_ro.parser', 'text/basics/1.txt')
    
    def test_03_basics(self):
        self.process('lang/basics/series.parser', 'text/basics/2.txt')
        self.process('lang/basics/count.parser', 'text/basics/2.txt')
        self.process('lang/basics/group.parser', 'text/basics/2.txt')
        self.process('lang/basics/option.parser', 'text/basics/2.txt')
        self.process('lang/basics/option_first.parser', 'text/basics/2.txt')
        self.process('lang/basics/first.parser', 'text/basics/1.txt')
        self.process('lang/basics/no_first_fail.parser', 'text/basics/1.txt', False)
        self.process('lang/basics/series_2.parser', 'text/basics/2.txt')
        self.process('lang/basics/series_3.parser', 'text/basics/2.txt')
    
    def test_04_basics(self):
        self.process('lang/basics/dup_discard.parser', 'text/basics/1.txt')
        self.process('lang/basics/dup_discard_fail.parser', 'text/basics/1.txt', False)
    
    def test_05_basics(self):
        self.process('lang/basics/previous.parser', 'text/basics/4.txt')
        self.process('lang/basics/previous_not.parser', 'text/basics/5.txt')

        self.process('lang/basics/string_compare.parser', 'text/basics/string_compare.txt')
        self.process('lang/basics/string_compare_fail.parser', 'text/basics/string_compare.txt', False)
        self.process('lang/basics/string_compare_nocase.parser', 'text/basics/string_compare_nocase.txt')
        self.process('lang/basics/string_compare_nocase_fail.parser', 'text/basics/string_compare_nocase.txt', False)
    
        self.process('lang/basics/range.parser', 'text/basics/range.txt')
        self.process('lang/basics/range_not.parser', 'text/basics/range.txt')
        self.process('lang/basics/range_priority.parser', 'text/basics/range.txt')

        self.process('lang/basics/and_token.parser', 'text/basics/1.txt')
        self.process('lang/basics/and_token_fail.parser', 'text/basics/1.txt', False)
        self.process('lang/basics/and_syntax.parser', 'text/basics/1.txt')
        self.process('lang/basics/and_syntax_fail.parser', 'text/basics/1.txt', False)

    def test_06_basics(self):
        self.process('func/ZTR_pass_01.parser', 'func/text_01')
        self.process('func/ZTS_pass_01.parser', 'func/text_01')
        self.process('func/ZPR_pass_01.parser', 'func/text_01')
        self.process('func/ZPR_pass_02.parser', 'func/text_01')
        self.process('func/ZPS_pass_01.parser', 'func/text_01')
        self.process('func/ZPS_pass_02.parser', 'func/text_01')

        self.process('func/ZTN_pass_01.parser', 'func/text_01')
        self.process('func/ZPN_pass_01.parser', 'func/text_01')

        self.process('func/NUL_pass_01.parser', 'func/text_nul')
    
    def test_07_basics(self):
        self.process('lang/logic/and.parser', 'func/text_01', False)
        self.process('lang/logic/and_02.parser', 'func/text_01', False)
        self.process('lang/logic/scope.parser', 'func/text_01')
    
    def test_08_basics(self):
        self.process('lang/basics/newline.parser', 'text/basics/newlines-linux.txt')
        self.process('lang/basics/spaces.parser', 'text/basics/spaces.txt')
        self.process('lang/basics/tokenizer_first.parser', 'text/basics/first_entry.txt')
        self.process('lang/basics/entrypoint_first.parser', 'text/basics/first_entry.txt')

    def test_09_basics(self):
        self.process('lang/basics/define.parser', 'text/basics/define.json')
        self.process('lang/basics/define_compare_char.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/alias_token.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/alias_syntax.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/define_count.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_count.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_define_count_01.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_define_count_02.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_define_count_03.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_define_count_04.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_tokenphase.parser', 'text/basics/define.json')
        self.process('lang/basics/variable_syntaxphase1.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_syntaxphase2.parser', 'text/basics/define.json')
        self.process('lang/basics/byte.parser', 'text/basics/alphabet_uppercase_split_unicode_combo')
        self.process('lang/basics/word.parser', 'text/basics/word_number_alphabet_uppercase')
        self.process('lang/basics/dword.parser', 'text/basics/dword_number_alphabet_uppercase')
        self.process('lang/basics/qword.parser', 'text/basics/qword_number_alphabet_uppercase')
        self.process('lang/basics/if_else.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/if_else_syntaxphase.parser', 'text/basics/alphabet_uppercase')
    
    def test_10_basics(self):
        self.process('lang/basics/push_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/push_complex_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/store_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/variable_count_syntaxphase.parser', 'text/basics/count_alphabet_uppercase')
        self.process('lang/basics/variable_point_syntaxphase.parser', 'text/basics/v_point_syntax')
        self.process('lang/basics/pop_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/pop_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/peek_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/peek_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/convert_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/convert_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_gt_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_gt_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_ge_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_ge_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_lt_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_lt_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_le_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_le_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_eq_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_eq_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_ne_tokenphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/arith_ne_syntaxphase.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/TpIAC.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/TpPTC.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/TpPA.parser', 'text/basics/alphabet_uppercase')
        self.process('lang/basics/TpSpecial_3.parser', 'text/basics/alphabet_uppercase')

    def test_10_minimal(self):
        self.process('lang/minimal', 'text/minimal')
    
    def test_20_json(self):
        self.process('lang/json', 'text/json')
    
    def test_20_json_extra(self):
        self.process('lang/json', 'text/json-extra/fail02.json', False)
        self.process('lang/json', 'text/json-extra/fail03.json', False)
        self.process('lang/json', 'text/json-extra/fail04.json', False)
        self.process('lang/json', 'text/json-extra/fail06.json', False)
        self.process('lang/json', 'text/json-extra/fail08.json', False)
        self.process('lang/json', 'text/json-extra/fail09.json', False)
        self.process('lang/json', 'text/json-extra/fail11.json', False)
        self.process('lang/json', 'text/json-extra/fail13.json', False)
        self.process('lang/json', 'text/json-extra/pass02.json')
        self.process('lang/json', 'text/json-extra/pass03.json')
        self.process('lang/json', 'text/json-extra/pass01.json')
    
    def test_30_c(self):
        self.process('lang/c', 'text/c')

if __name__ == '__main__':
    unittest.main(verbosity=2)
    
