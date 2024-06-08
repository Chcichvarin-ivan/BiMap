/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-06-08 14:39:36
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-08 14:43:36
 * @FilePath: /BiMap/bimap.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <optional>
#include <string_view>

class BiMap {
public:
    /**
     * Добавляет в словарь пару "ключ-значение".
     * В случае успеха возвращает true.
     * Возвращает false, если ключ или значение были ранее добавлены.
     * 
     * Метод обеспечивает строгую гарантию безопасности исключений
     */
    bool Add(std::string_view key, std::string_view value);

    /**
     * Возвращает значение, связанное с ключом, либо nullopt, если такого ключа нет
     */
    std::optional<std::string_view> FindValue(std::string_view key) const noexcept;

    /**
     * Возвращает ключ, связанный с value, либо nullopt, если такого значения нет
     */
    std::optional<std::string_view> FindKey(std::string_view value) const noexcept;

private:
    struct Impl;
    
    std::unique_ptr<Impl> impl_;
};