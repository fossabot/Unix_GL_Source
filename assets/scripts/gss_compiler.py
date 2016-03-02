import sys, os, re


def read_file(gss_filename):
    gss_file_path = str(os.path.realpath(__file__))[:-15] + gss_filename
    with open(gss_file_path, 'r') as gssfile:
        code = gssfile.read()
        return code


def trim_expression_from_input(inp):
    parts = inp.split("\t")
    out = ""
    for p in parts:
        out += p

    parts = out.split("\n")
    out = ""
    for p in parts:
        out += p

    parts = out.split(" ")
    out = ""
    for p in parts:
        out += p

    return out


def compile_timeline(code):
    code = trim_expression_from_input(code)
    func_head = "@timeline"
    func_opening_bracket = "\{"
    func_closing_bracket = "\}"
    func_elements = "([0-9]+\:\"\.[a-z-A-Z-0-9-\_]+\")"
    func_elements_extension = "\,([0-9]+\:\"\.[a-z-A-Z-0-9]+\")"
    func_params_count = 1


    p = re.compile(func_head + func_opening_bracket + func_elements + func_closing_bracket)
    if p.match(code) != None:
        print("Timeline : " + str(p.match(code).groups()))
    else:
        while 1:
            if func_params_count > 100:
                print("ERROR::REQUIREMENTS NOT SATISFIED !")
                break
            func_params_count += 1
            func_elements += func_elements_extension

            p = re.compile(func_head + func_opening_bracket + func_elements + func_closing_bracket)
            if p.match(code) != None:
                print("The Timeline is : " + str(p.match(code).groups()))
                break


def compile_styles(code):
    code = trim_expression_from_input(code)
    func_head = "#[a-z-A-Z]+"
    func_opening_bracket = "\{"
    func_closing_bracket = "\}"
    func_elements = "([a-z]+[\:]{1}[a-z]+)"
    func_elements_extension = "\,([a-z]+[\:]{1}[a-z]+)"
    func_params_count = 1


    p = re.compile(func_head + func_opening_bracket + func_elements + func_closing_bracket)
    if p.match(code) != None:
        print("The Styles are : " + str(p.match(code).groups()))
    else:
        while 1:
            if func_params_count > 100:
                print("ERROR::REQUIREMENTS NOT SATISFIED !")
                break
            func_params_count += 1
            func_elements += func_elements_extension

            p = re.compile(func_head + func_opening_bracket + func_elements + func_closing_bracket)
            if p.match(code) != None:
                print("The Styles are : " + str(p.match(code).groups()))
                break


def compile_code(code):
    compile_timeline(code)
    compile_styles(code)


if __name__ == '__main__':
    if len(sys.argv) > 1:
        fn = read_file(sys.argv[1])
        compile_code(fn)
