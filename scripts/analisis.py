# Análisis de resultados: lee data/resultados.csv, calcula estadística descriptiva
# y genera las tablas y figuras del artículo.
# Uso (desde la carpeta del proyecto):  python scripts/analisis.py

import csv
import os
import statistics as st
import matplotlib
matplotlib.use("Agg")            # para guardar imágenes sin abrir ventanas
import matplotlib.pyplot as plt

ARCHIVO = "data/resultados.csv"
CARPETA_FIGURAS = "docs/figuras"
os.makedirs(CARPETA_FIGURAS, exist_ok=True)

ALGORITMOS = ["Insercion", "ShellSort"]
PATRONES = ["aleatorio", "ascendente", "descendente"]

# 1. Leo el CSV y agrupo los valores por (algoritmo, n, patrón)
grupos = {}
with open(ARCHIVO, newline="") as f:
    for fila in csv.DictReader(f):
        clave = (fila["algoritmo"], int(fila["n"]), fila["patron"])
        g = grupos.setdefault(clave, {"tiempo": [], "comp": [], "interc": []})
        g["tiempo"].append(float(fila["tiempo_ms"]))
        g["comp"].append(int(fila["comparaciones"]))
        g["interc"].append(int(fila["intercambios"]))

tamanos = sorted({k[1] for k in grupos})

def resumen(valores):
    # promedio, mediana, desviación estándar, mínimo y máximo
    desv = st.stdev(valores) if len(valores) > 1 else 0.0
    return st.mean(valores), st.median(valores), desv, min(valores), max(valores)

# 2. Estadística descriptiva completa -> data/estadisticas.csv
with open("data/estadisticas.csv", "w", newline="") as f:
    w = csv.writer(f)
    w.writerow(["algoritmo", "n", "patron", "repeticiones", "metrica",
                "promedio", "mediana", "desv_est", "minimo", "maximo"])
    for alg in ALGORITMOS:
        for n in tamanos:
            for pat in PATRONES:
                g = grupos.get((alg, n, pat))
                if not g:
                    continue
                for nombre, clave in [("tiempo_ms", "tiempo"),
                                      ("comparaciones", "comp"),
                                      ("intercambios", "interc")]:
                    m, med, d, mn, mx = resumen(g[clave])
                    w.writerow([alg, n, pat, len(g[clave]), nombre,
                                round(m, 4), round(med, 4), round(d, 4),
                                round(mn, 4), round(mx, 4)])
print("Guardado data/estadisticas.csv")

# 3. Tabla 1: tiempo (ms), promedio ± desviación estándar
print("\nTABLA 1. Tiempo de ejecución (ms), promedio ± desviación estándar")
print("n | patrón | Inserción | Shell sort")
for n in tamanos:
    for pat in PATRONES:
        celdas = []
        for alg in ALGORITMOS:
            m, _, d, _, _ = resumen(grupos[(alg, n, pat)]["tiempo"])
            celdas.append(f"{m:.4f} ± {d:.4f}")
        print(f"{n} | {pat} | {celdas[0]} | {celdas[1]}")

# 4. Tabla 2: comparaciones e intercambios (promedio)
print("\nTABLA 2. Comparaciones e intercambios (promedio)")
print("n | patrón | Inserción comp. | Inserción interc. | Shell comp. | Shell interc.")
for n in tamanos:
    for pat in PATRONES:
        vals = []
        for alg in ALGORITMOS:
            g = grupos[(alg, n, pat)]
            vals += [st.mean(g["comp"]), st.mean(g["interc"])]
        print(f"{n} | {pat} | " + " | ".join(f"{v:.0f}" for v in vals))

# 5. Figura 1: boxplot del tiempo por algoritmo, con el n más grande medido
n_max = tamanos[-1]
fig, ejes = plt.subplots(1, 3, figsize=(12, 4))
for ax, pat in zip(ejes, PATRONES):
    datos = [grupos[(alg, n_max, pat)]["tiempo"] for alg in ALGORITMOS]
    ax.boxplot(datos)
    ax.set_xticks([1, 2])
    ax.set_xticklabels(["Inserción", "Shell sort"])
    ax.set_title(f"Patrón {pat}")
    ax.set_ylabel("Tiempo (ms)")
    ax.set_yscale("log")
fig.suptitle(f"Distribución del tiempo de ejecución (n = {n_max}, 30 repeticiones)")
fig.tight_layout()
fig.savefig(f"{CARPETA_FIGURAS}/figura1_boxplot.png", dpi=200)
plt.close(fig)

# 6. Figura 2: curva n contra tiempo promedio (escala logarítmica)
fig, ejes = plt.subplots(1, 3, figsize=(12, 4))
for ax, pat in zip(ejes, PATRONES):
    for alg, nombre in zip(ALGORITMOS, ["Inserción", "Shell sort"]):
        medias = [st.mean(grupos[(alg, n, pat)]["tiempo"]) for n in tamanos]
        ax.plot(tamanos, medias, marker="o", label=nombre)
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xlabel("n (tamaño del arreglo)")
    ax.set_ylabel("Tiempo promedio (ms)")
    ax.set_title(f"Patrón {pat}")
    ax.legend()
fig.suptitle("Tiempo promedio según el tamaño de entrada")
fig.tight_layout()
fig.savefig(f"{CARPETA_FIGURAS}/figura2_n_tiempo.png", dpi=200)
plt.close(fig)
print(f"\nFiguras guardadas en {CARPETA_FIGURAS}/")
