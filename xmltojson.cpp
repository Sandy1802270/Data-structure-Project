#include "xmltojson.h"





std::stack<Node*> stack_for_list;
std::stack<int> index;

std::string  XML_to_json(Node* root) {
    //Not List and have children
    if (!Node_list(root->parent) && root->children.size() != 0) {

        indentation(root->level);
        output5 += "\"";
        output5 += root->Tag_Name ;
        output5 +="\":" ;
        output5 +="{" ;
        output5 +="\r\n";
        for (int i = 0; i < root->children.size(); i++) {
            XML_to_json(root->children[i]);
            if (i < root->children.size() - 1) {
                output5 += ',' ;
                output5 += "\r\n";
            }
        }
        output5 +="\r\n";
        indentation(root->level);
        output5 += "}" ;

    }//Not list and leaf Node
    else if (!Node_list(root->parent) && root->children.size() == 0) {
        indentation(root->level);
        output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":";
        if (isdigit(root->Tag_value[0])) {
            output5+= root->Tag_value ;
        }
        else {
            output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"";
        }
    }//List and have children
    else if (Node_list(root->parent) && root->children.size() != 0) {
        int size_of_list = root->parent->children.size();

            if (stack_for_list.empty()) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name;
                output5 += "\":" ;
                output5 +="[" ;
                output5 += "\r\n";
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";

                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";

            }
            else if (stack_for_list.top()->Tag_Name != root->Tag_Name) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":" ;
                output5 +="[" ;
                output5 +="\r\n";
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";

                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 +="\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                //XML_to_json(root->children[i]);/
            }
            else if (index.top() == size_of_list) {
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";
                stack_for_list.pop();

                index.pop();
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                //XML_to_json(root->children[i]);/

                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                output5 += "\r\n";
                indentation(root->level-1);
                output5 += "  ";
                output5+= "]";
            }
            else {
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                //XML_to_json(root->children[i]);/
            }


    }//List and don't have children
    else {
        int size_of_list = root->parent->children.size();

        //index Calculation


            if (stack_for_list.empty()) {
                indentation(root->level);
                output5 += "\"" ;
                        output5 +=root->Tag_Name ;
                        output5 +="\":" ;
                output5 +="[" ;
                          output5 +="\r\n";
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);

                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);

                    output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"" ;
                }


                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
            }
            else if(stack_for_list.top()->Tag_Name != root->Tag_Name) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":" ;
                output5 +="[" ;
                output5 +="\r\n";
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                            output5 +=root->Tag_value;
                            output5 += "\"" ;
                }


                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
            }
            else if (index.top() == size_of_list) {
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"" ;
                }

                stack_for_list.pop();
                index.pop();
                output5 += "\r\n";
                indentation(root->level);
                output5+= "]";
            }
            else {
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                    output5 +=root->Tag_value;
                    output5 += "\"" ;
                }

            }

        }
return output5;
    }
