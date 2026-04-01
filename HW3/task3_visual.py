import matplotlib.pyplot as plt
import numpy as np


def main():
    A = np.array([-3.0, -1.0])
    B = np.array([4.0, 1.0])
    C = np.array([-1.0, 3.0])
    S = np.array([-2.0, 2.0])

    H1 = np.array([0.111111, -0.111111])
    H2 = np.array([0.679198, 2.328321])

    N1 = np.array([-0.274721, 0.961524])
    N2 = np.array([-0.371391, -0.928477])
    R2 = np.array([-0.507442, -0.861686])

    End = H2 + (R2 * 3.0)

    fig, ax = plt.subplots(figsize=(10, 8))
    ax.set_aspect("equal")
    ax.grid(True, linestyle="--", alpha=0.6)
    ax.set_title("Bullet Ricochet Visualization", fontsize=14, fontweight="bold")
    ax.set_xlabel("X-axis")
    ax.set_ylabel("Y-axis")

    ax.plot([A[0], B[0]], [A[1], B[1]], color="black", linewidth=3, label="Wall 1 (AB)")
    ax.plot([B[0], C[0]], [B[1], C[1]], color="black", linewidth=3, label="Wall 2 (BC)")

    ax.plot(
        [S[0], H1[0]],
        [S[1], H1[1]],
        color="gold",
        linestyle="-",
        linewidth=2,
        label="Bullet Path",
    )
    ax.plot([H1[0], H2[0]], [H1[1], H2[1]], color="gold", linestyle="-", linewidth=2)

    ax.annotate(
        "", xy=End, xytext=H2, arrowprops=dict(arrowstyle="->", color="gold", lw=2)
    )
    ax.annotate(
        "",
        xy=H1 + N1,
        xytext=H1,
        arrowprops=dict(arrowstyle="->", color="blue", lw=1.5),
        label="Normals",
    )
    ax.annotate(
        "",
        xy=H2 + N2,
        xytext=H2,
        arrowprops=dict(arrowstyle="->", color="blue", lw=1.5),
    )

    points = {"A": A, "B": B, "C": C, "S": S, "H1": H1, "H2": H2}
    point_details = {
        "A": "Wall 1 start",
        "B": "Shared wall corner",
        "C": "Wall 2 end",
        "S": "Bullet start",
        "H1": "First hit point",
        "H2": "Second hit point",
    }

    for name, pt in points.items():
        ax.plot(pt[0], pt[1], marker="o", color="darkblue", markersize=6)
        ax.text(
            pt[0] - 0.1,
            pt[1] + 0.15,
            name,
            fontsize=12,
            fontweight="bold",
            color="darkred",
        )

    hover_label = ax.annotate(
        "",
        xy=(0.0, 0.0),
        xytext=(12, 12),
        textcoords="offset points",
        fontsize=10,
        bbox=dict(
            boxstyle="round,pad=0.3", facecolor="white", edgecolor="black", alpha=0.9
        ),
        arrowprops=dict(arrowstyle="->", color="black", lw=1.0),
    )
    hover_label.set_visible(False)

    def on_hover(event):
        if event.inaxes != ax or event.xdata is None or event.ydata is None:
            if hover_label.get_visible():
                hover_label.set_visible(False)
                fig.canvas.draw_idle()
            return

        mouse = np.array([event.xdata, event.ydata])
        nearest_name = None
        nearest_point = None
        nearest_distance = float("inf")

        for name, pt in points.items():
            distance = np.linalg.norm(mouse - pt)
            if distance < nearest_distance:
                nearest_distance = distance
                nearest_name = name
                nearest_point = pt

        hover_radius = 0.3
        if nearest_name is not None and nearest_distance <= hover_radius:
            hover_label.xy = (nearest_point[0], nearest_point[1])
            hover_label.set_text(
                f"{nearest_name}\n"
                f"x = {nearest_point[0]:.6f}\n"
                f"y = {nearest_point[1]:.6f}\n"
                f"{point_details[nearest_name]}"
            )
            hover_label.set_visible(True)
            fig.canvas.draw_idle()
        elif hover_label.get_visible():
            hover_label.set_visible(False)
            fig.canvas.draw_idle()

    fig.canvas.mpl_connect("motion_notify_event", on_hover)

    ax.set_xlim(-4, 5)
    ax.set_ylim(-3, 5)

    handles, labels = ax.get_legend_handles_labels()
    by_label = dict(zip(labels, handles))
    ax.legend(by_label.values(), by_label.keys(), loc="upper left")

    plt.show()


if __name__ == "__main__":
    main()
