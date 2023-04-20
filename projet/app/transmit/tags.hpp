/**
 * Constants used to generate the SVG file.
 *
 * USAGE:
 *  send(tags::OPENING);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date April 19th, 2023
 */

#ifndef TAGS_H
#define TAGS_H

namespace tags {
    static constexpr const char OPENING[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        "width=\"100%\" height=\"100%\" viewBox=\"0 0 1100 550\">";

    static constexpr const char CLOSING[] = "</g></g></svg>";

    static constexpr const char STYLE[] =
        "<style>"
        "text {font-family: \"Arial\"; font-size: 20px; fill: blue;}"
        "#map {fill: #eee; stroke: black;} circle {fill: gray;}"
        "polygon, circle {stroke: black; stroke-width: 0.02px;}"
        "</style>";

    static constexpr const char CENTER_GROUP[] =
        "<g transform=\"translate(100)\">";

    static constexpr const char TITLE[] =
        "<text y=\"35\">section 02 -- &#xE9;quipe 4546 -- L&#xE9;opard</text>";

    static constexpr const char BOX[] =
        "<rect id=\"map\" y=\"50\" width=\"900\" height=\"450\" />";

    static constexpr const char MAP[] =
        "<g transform=\"translate(100,425) scale(100,-100)\">";

    namespace dots {
        static constexpr const char ROW[] = "<g id=\"row\" y=\"0\">";

        static constexpr const char DOT[] =
            "<rect id=\"square\" x=\"0\" width=\"0.1\" height=\"0.1\" "
            "transform=\"translate(-0.05,-0.05)\" />";

        static constexpr const char ADDITIONAL_DOTS[] =
            "<use href=\"#square\" x=\"1\" /><use href=\"#square\" x=\"2\" />"
            "<use href=\"#square\" x=\"3\" /><use href=\"#square\" x=\"4\" />"
            "<use href=\"#square\" x=\"5\" /><use href=\"#square\" x=\"6\" />"
            "<use href=\"#square\" x=\"7\" />";

        static constexpr const char ROW_END[] = "</g>";

        static constexpr const char ADDITIONAL_ROWS[] =
            "<use href=\"#row\" y=\"1\" /><use href=\"#row\" y=\"2\" />"
            "<use href=\"#row\" y=\"3\" />";

        static constexpr const char RED[] =
            "<use href=\"#square\" fill=\"red\" />";
    } // namespace dots

    namespace templates {
        static constexpr const char POINT[] = "%d,%d ";

        static constexpr const char AREA[] =
            "<text y=\"530\">AIRE: %u pouces carr&#xE9;s</text>";

        static constexpr const char POLYGON[] =
            "<polygon fill=\"forestgreen\" points=\"%s\" />";

        static constexpr const char POLE[] =
            "<circle cx=\"%u\" cy=\"%u\" r=\"0.15\" />";
    } // namespace templates

} // namespace tags

#endif
