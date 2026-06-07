import re
import sys

def parse_pas_file(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    constants = {}
    const_pattern = re.compile(r'const\s+(\w+)\s*=\s*[\'"]([^\'"]+)[\'"];')
    for match in const_pattern.finditer(content):
        constants[match.group(1)] = match.group(2)
    
    var_const_pattern = re.compile(r'var\s+(\w+)\s*:=\s*[\'"]([^\'"]+)[\'"];')
    for match in var_const_pattern.finditer(content):
        constants[match.group(1)] = match.group(2)

    struct_pattern = re.compile(r"wbStruct(?:SK|ExSK)?\s*\(\s*([^,)]+)\s*,\s*([^,)]+)\s*,\s*\[(.*?)\]\s*\)", re.DOTALL)
    
    results = []
    
    for match in struct_pattern.finditer(content):
        sig_raw = match.group(1).strip().strip("'").strip('"')
        label_raw = match.group(2).strip().strip("'").strip('"')
        fields_block = match.group(3)
        sig = constants.get(sig_raw, sig_raw)
        if len(sig) != 4 and sig not in ['NPC_', 'SCOL']:
             if not sig.isupper():
                 continue
        field_pattern = re.compile(r"wb(Integer|Float|String|FormID)\s*\(\s*([^,)]+)\s*(?:,\s*([^,)]+))?\s*\)")
        tags = []
        seen_tags = set()
        for f_match in field_pattern.finditer(fields_block):
            f_type_name = f_match.group(1)
            f_tag_raw = f_match.group(2).strip().strip("'").strip('"')
            tag = constants.get(f_tag_raw, f_tag_raw)
            if tag in seen_tags:
                continue
            cpp_type = "FieldType::Unknown"
            if f_type_name == "Integer": cpp_type = "FieldType::Int32"
            elif f_type_name == "Float": cpp_type = "FieldType::Float"
            elif f_type_name == "String": cpp_type = "FieldType::String"
            elif f_type_name == "FormID": cpp_type = "FieldType::FormID"
            label_text = f_tag_raw
            tags.append((tag, label_text, cpp_type))
            seen_tags.add(tag)
        if tags:
            results.append((sig, label_raw, tags))
    return results

def generate_cpp(results):
    unique_results = {}
    for sig, label, tags in results:
        if sig not in unique_results or len(tags) > len(unique_results[sig][1]):
            unique_results[sig] = (label, tags)
    output = ["inline std::map<std::string, RecordSchema> g_RecordSchemas = {"]
    sorted_sigs = sorted(unique_results.keys())
    for sig in sorted_sigs:
        label, tags = unique_results[sig]
        line = f'    {{"{sig}", {{"{label}", {{'
        tag_lines = []
        for tag, tag_label, type_ in tags:
            tag_lines.append(f'        {{"{tag}", {{"{tag_label}", {type_}}}}}')
        line += "\n" + ",\n".join(tag_lines)
        line += "\n    }}},"
        output.append(line)
    output.append("};")
    return "\n".join(output)

if __name__ == "__main__":
    results = parse_pas_file("starfield/vendor/tes5edit/Core/wbDefinitionsSF1.pas")
    print(generate_cpp(results))
