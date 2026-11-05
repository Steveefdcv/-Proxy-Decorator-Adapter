#include <iostream>
#include <string>
#include <algorithm>

class Text {
public:
    virtual ~Text() = default;
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    ~DecoratedText() override { delete text_; }
protected:
    Text* text_;
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string reversed(data);
        std::reverse(reversed.begin(), reversed.end());
        text_->render(reversed);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    void render(const std::string& href, const std::string& data) const {
        std::cout << "<a href=" << href << ">";
        text_->render(data);
        std::cout << "</a>";
    }

    void render(const std::string& data) const override {
        text_->render(data);
    }
};

int main() {
    auto paragraph = new Paragraph(new Text());
    paragraph->render("Hello world");
    std::cout << std::endl;   // <p>Hello world</p>
    delete paragraph;

    auto reversed = new Reversed(new Text());
    reversed->render("Hello world");
    std::cout << std::endl;   // dlrow olleH
    delete reversed;

    auto link = new Link(new Text());
    link->render("netology.ru", "Hello world");
    std::cout << std::endl;   // <a href=netology.ru>Hello world</a>
    delete link;

    return 0;
}