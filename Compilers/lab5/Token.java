public class Token {
    String domain, attribute;
    Fragment fragment;


    Token(String s1, String s2, Fragment fragment) {
        this.domain = s1;
        this.attribute = s2;
        this.fragment = fragment;
    }

    public String getDomain() {
        return domain;
    }

    public String getAttribute() {
        return attribute;
    }

    @Override
    public String toString() {
        return  domain + " " + fragment.toString() + ": " + attribute ;

    }
}