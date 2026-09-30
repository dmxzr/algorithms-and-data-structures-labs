import pandas as pd

# Чтение данных из файла time_date.txt
with open('time_data.txt', 'r') as file:
    time_values = [float(line.strip()) for line in file]

# Убедимся, что массивы имеют одинаковую длину
number_of_nodes = [
    1000000, 2000000, 3000000, 4000000,
    5000000, 6000000, 7000000, 8000000,
    9000000, 10000000
]

# Проверка длины массивов
if len(number_of_nodes) != len(time_values):
    raise ValueError("Количество узлов и количество времен должны совпадать.")

# Данные
data = {
    'Number of Nodes': number_of_nodes,
    'Time (seconds)': time_values
}

# Создание DataFrame
df = pd.DataFrame(data)

# Создание Excel-файла
excel_file = 'graph_data.xlsx'
writer = pd.ExcelWriter(excel_file, engine='xlsxwriter')

# Запись DataFrame в Excel
df.to_excel(writer, sheet_name='Data', index=False)

# Получение объекта книги и листа
workbook = writer.book
worksheet = writer.sheets['Data']

# Настройка графика
chart = workbook.add_chart({'type': 'line'})

# Добавление данных в график
chart.add_series({
    'name': 'Nodes/times',
    'categories': f'Data!$A$2:$A${len(df)+1}',  # Заголовки категорий
    'values': f'Data!$B$2:$B${len(df)+1}',     # Значения
})

# Настройки графика
chart.set_x_axis({'name': 'Number of Nodes', 'name_font': {'size': 12}})
chart.set_y_axis({'name': 'Time (seconds)', 'name_font': {'size': 12}})
chart.set_title({'name': 'Time vs Number of Nodes'})

# Запись графика на лист
worksheet.insert_chart('D2', chart)

# Закрытие писателя Excel
writer.close()

print(f"График таймирования успешно сохранен в файл: {excel_file}")
