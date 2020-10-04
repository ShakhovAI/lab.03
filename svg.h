#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
using namespace std;

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n" << '\n';
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<text<<"</text>" << '\n';
}

void svg_end()
{
    cout <<'\n'<< "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fil){
  cout << "<rect x='" << x << "' y='" << y <<"' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fil << "' />" << '\n';
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 400;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 50;



    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    int top = 0;

    for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    switch (top){
    case 0: svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
        break;
    case 30: svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "green", "green");
        break;
    case 60: svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "blue");
        break;
}
    top += BIN_HEIGHT;
    }
    svg_end();
}

#endif // SVG_H_INCLUDED
