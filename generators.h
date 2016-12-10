#pragma once

#include <string>
#include <vector>

class Generators {
  public:

    static std::string generate_name();

    static std::string generate_conference_name();
    static std::string generate_conference_email_subject(const std::string& conf_name);
    static std::string generate_conference_email_body(const std::string& conf_name, const std::string& from, const std::string& month);

  private:

    typedef std::vector<std::string> StringSet;

    static std::string random_element(StringSet set);
    static void replace_all(std::string& string, const std::string& search, const std::string& replace);

    static const StringSet first_names_, last_names_;
    static const StringSet cities_;
    static const StringSet conference_nouns_, conference_endings_, conference_subjects_;
    static const StringSet conference_email_leaders_;
    static const StringSet email_greetings_, email_signoffs_;
};
