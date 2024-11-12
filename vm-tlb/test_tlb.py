import subprocess
from typing import List, Tuple, Optional
import numpy as np
import matplotlib.pyplot as plt

def run_tlb(num_pages: int, num_trials: int) -> Optional[float]:
    """
    Runs the tlb program with the specified parameters and returns the average access time.

    Parameters:
    - num_pages (int): Number of pages to access in each run of the tlb program.
    - num_trials (int): Number of repetitions within the tlb program to average access time.

    Returns:
    - float or None: The average access time per page in nanoseconds, or None if an error occurs.
    """
    result = subprocess.run(
        ["./tlb", str(num_pages), str(num_trials)], capture_output=True, text=True
    )
    
    # print(result)
    if result.returncode != 0:
        print(f"Error running tlb with {num_pages} pages and {num_trials} trials:")
        print(result.stderr)
        return None
    
    # Parse the output to get the average time per page access
    output_lines: List[str] = result.stdout.splitlines()
    # print(output_lines)
    for line in output_lines:
        if "Average time per page access" in line:
            avg_time: float = float(line.split(":")[1].strip().split()[0])
            return avg_time
    return None

def gather_data(max_pages: int = 4096, trials_per_page: int = 10, num_trials: int = 10) -> Tuple[List[int], List[Optional[float]]]:
    """
    Gathers timing data for varying page counts by running the tlb program.

    Parameters:
    - max_pages (int): Maximum number of pages to test; each test doubles the page count up to this limit.
    - trials_per_page (int): Number of repetitions within the tlb program to smooth out measurement noise.
    - num_trials (int): Number of times to run the tlb program per page count for statistical averaging.

    Returns:
    - Tuple[List[int], List[float or None]]: Lists of page counts tested and their average times per page access.
    """
    page_counts: List[int] = []
    avg_times: List[Optional[float]] = []
    
    num_pages: int = 1
    while num_pages <= max_pages:
        page_counts.append(num_pages)

        # Run the tlb program for the current number of pages multiple times and average the results
        trial_times: List[float] = []
        for _ in range(num_trials):
            avg_time: Optional[float] = run_tlb(num_pages, trials_per_page)
            if avg_time is not None:
                trial_times.append(avg_time)
        
        # Calculate the mean of the trials
        if trial_times:
            mean_time: float = np.mean(trial_times)
            avg_times.append(mean_time)
            print(f"Pages: {num_pages}, Avg time per access: {mean_time:.2f} ns")
        else:
            avg_times.append(None)
        
        # Double the number of pages for the next iteration
        num_pages *= 2
    
    return page_counts, avg_times

def plot_data(page_counts: List[int], avg_times: List[Optional[float]]) -> None:
    """
    Plots the page count vs. average time per page access.

    Parameters:
    - page_counts (List[int]): List of page counts tested.
    - avg_times (List[float or None]): List of average access times corresponding to each page count.
    """
    plt.figure(figsize=(10, 6))
    plt.plot(page_counts, avg_times, marker="o", linestyle="-")
    plt.xlabel("Number of Pages")
    plt.ylabel("Average Time per Page Access (ns)")
    plt.title("Page Count vs. Average Time per Page Access")
    plt.xscale("log")
    # plt.yscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.show()

# Run the data gathering and plot the results
page_counts, avg_times = gather_data(max_pages=4096, trials_per_page=100, num_trials=10)
plot_data(page_counts, avg_times)
