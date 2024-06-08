/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-06-08 14:38:59
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-08 14:41:36
 * @FilePath: /BiMap/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <cassert>

#include "bimap.h"

int main() {
    using namespace std::literals;

    BiMap bimap;
    {
        const bool cat_added = bimap.Add("Cat"sv, "Koshka"sv);

        assert(cat_added);

        assert(bimap.FindValue("Cat"sv) == "Koshka"sv);
        assert(bimap.FindKey("Koshka"sv) == "Cat"sv);
        assert(!bimap.FindKey("Cat"sv));
        assert(!bimap.FindValue("Koshka"sv));

        const bool kitty_added = bimap.Add("Cat"sv, "Kitty"sv);

        assert(!kitty_added);
        assert(bimap.FindValue("Cat"sv) == "Koshka"sv);
        assert(!bimap.FindValue("Kitty"sv));
    }

    BiMap bimap_copy(bimap);
    assert(bimap_copy.FindValue("Cat"sv) == "Koshka"sv);
    assert(bimap_copy.FindKey("Koshka"sv) == "Cat"sv);

    bimap_copy.Add("Dog"sv, "Sobaka"sv);
    assert(bimap_copy.FindValue("Dog"sv) == "Sobaka"sv);
    assert(bimap_copy.FindKey("Sobaka"sv) == "Dog"sv);
    assert(!bimap.FindKey("Sobaka"sv));
    assert(!bimap.FindValue("Dog"sv));

    bimap = std::move(bimap_copy);
    assert(bimap.FindValue("Dog"sv) == "Sobaka"sv);
    assert(bimap.FindKey("Sobaka"sv) == "Dog"sv);

    BiMap moved_bimap(std::move(bimap));
    assert(moved_bimap.FindValue("Dog"sv) == "Sobaka"sv);
    assert(moved_bimap.FindKey("Sobaka"sv) == "Dog"sv);

    BiMap bimap_to_assign;
    bimap_to_assign = moved_bimap;
    assert(bimap_to_assign.FindValue("Dog"sv) == "Sobaka"sv);
    assert(bimap_to_assign.FindKey("Sobaka"sv) == "Dog"sv);
}